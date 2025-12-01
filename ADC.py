'''
File Name: ADC.py
Assignment: Project 2
Lab Section: B02
Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
Submission Date: December 1, 2025
 '''

import serial
import time
import pandas as pd
import matplotlib.pyplot as plt
import sys

port_name = '/dev/tty.usbserial-0001' # MacOS
# port_name = 'COM3'                      # Windows
baud_rate = 9600
buffer = []
intensity = []
sample_times = []

try:
    # Connect python program to USB UART
    ser = serial.Serial(port_name, baud_rate)
    print(f"Connected to {port_name}.")
    time.sleep(2)
    
    # Waiting for UART transmission
    while True:
        if ser.in_waiting > 0:
            msg = ser.readline().decode().replace('\x00', '')
            
            # Transmission started
            if msg == "START_READING\n":
                print("Sampling data...")
                start_time = time.time()

                # Receive ADC and Intensity values from the C program that is transmitted over UART
                while time.time() - start_time <= 60:
                    if ser.in_waiting > 0:
                        sample_msg = ser.readline().decode().replace('\x00', '')

                        # sample_msg is in the form 10230 or 10231

                        # Stop sampling when C program stops transmitting
                        if (sample_msg == "STOP_READING\n"):
                            break

                        buffer_data = int(sample_msg[0:4])
                        buffer.append(buffer_data)

                        # 1 is LED on, 0 is LED off (during LED blinking)
                        if int(sample_msg[4:]) == 1:
                            intensity.append((float(buffer_data) / 1023) * 100)
                        else:
                            intensity.append(0)
                        sample_times.append(time.time() - start_time)
                
                print("Finished sampling")

                # Save data into a CSV file
                df = pd.DataFrame({
                    'Time (s)': sample_times,
                    'ADC Reading': buffer,
                    'Intensity (Duty Cycle %)': intensity
                })
                df.to_csv('Group1.csv', index=False)

                # Output the graphs of ADC reading vs. time, and Intensity vs. time
                fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(8, 6), sharex=True)

                ax1.plot(sample_times, buffer, 'b-', label='Buffer')
                ax1.set_ylabel('ADC Reading')
                ax1.set_xlabel('Time (s)')
                ax1.set_title('ADC Reading (Raw)')
                ax1.set_ylim([0, 1023])
                ax1.set_xlim(0)
                ax1.legend()
                ax1.grid(True)

                ax2.plot(sample_times, intensity, 'r-', label='Intensity')
                ax2.set_ylabel('Intensity (Duty Cycle %)')
                ax2.set_xlabel('Time (s)')
                ax2.set_title('LED Intensity')
                ax2.set_ylim([0, 100])
                ax2.set_xlim(0)
                ax2.legend()
                ax2.grid(True)

                plt.tight_layout()
                plt.show()

            else:
                print(msg)

            # Clear data
            buffer.clear()
            intensity.clear()
            sample_times.clear()

            continue
        time.sleep(0.1)
except serial.SerialException as e:
    print(f"Error opening or communicating with serial port: {e}.")
except KeyboardInterrupt:
    print("Exiting.")
finally:
    ser.close()
    print("Serial port closed.")
