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

port_name = '/dev/tty.usbserial-0001'
# port_name = 'COM4'
baud_rate = 4800
buffer = []
intensity = []
sample_times = []

try:
    # Connect python program to USB UART
    ser = serial.Serial(port_name, baud_rate)
    print(f"Connected to {port_name}.")
    time.sleep(2)
    
    # transmission can only happen in the on state, or on led blinking state

    # Waiting for UART transmission
    while True:
        if ser.in_waiting > 0:
            msg = ser.readline().decode().replace('\x00', '')

            # Transmission started
            if msg == "START_READING\n":
                print("Sampling data...")
                start_time = time.time()

                # sample for 1 minute, then stop
                # if the entire minute is used, C program can still be transmitting so I need
                # a way for the C program to stop transmitting as well
                # maybe some kind of counter in the T3 interrupt? Since T3 should be set to interrupt
                # at a constant rate

                # Receive ADC and Intensity values from the C program that is transmitted over UART
                while time.time() - start_time <= 60:
                    if ser.in_waiting > 0:
                        sample_msg = ser.readline().decode().replace('\x00', '').replace('\n', '')

                        # Stop sampling when C program stops transmitting
                        if (sample_msg == "STOP_READING"):
                            break

                        # need to think of how to send both intensity and buffer value in one transmit
                        # and how to separate them in the python program
                        # maybe just separate the values with a whitespace
                        buffer_data = sample_msg.lstrip('0')
                        if buffer_data == '':
                            buffer.append(0)
                            intensity.append(0)

                        else:
                            buffer.append(int(buffer_data))
                            intensity.append(float(buffer_data) * 0.00322265625) # need to change this
                        sample_times.append(time.time() - start_time)
                
                # Print buffer, intensity, and time values into the terminal
                print("Digital ADC Buffer Values:")
                print(buffer)
                print("Intensity Values:")
                print(intensity)
                print("Sample Times:")
                print(sample_times)

                # Save data into a CSV file
                df = pd.DataFrame({
                    'Sample Time (seconds)': sample_times,
                    'Digital ADC Buffer': buffer,
                    'Intensity': intensity
                })
                df.to_csv('Group1.csv', index=False)

                # Output the graphs of buffer vs. time, and Intensity vs. time
                fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(8, 6), sharex=True)

                ax1.plot(sample_times, buffer, 'b-o', label='Buffer')
                ax1.set_ylabel('Digital ADC Buffer')
                ax1.set_xlabel('Sample Time (seconds)')
                ax1.set_title('Digital ADC Buffer vs. Sample Time')
                ax1.legend()
                ax1.grid(True)

                ax2.plot(sample_times, intensity, 'r-o', label='Intensity')
                ax2.set_ylabel('Intensity')
                ax2.set_xlabel('Sample Time (seconds)')
                ax2.set_title('Intensity vs. Sample Time')
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
