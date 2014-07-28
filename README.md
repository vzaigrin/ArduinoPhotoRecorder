## Arduino Photo Fixator 

This is Standalone Photo Fixator based on Arduino.

It use Weatherproof TTL Serial JPEG Camera (https://www.adafruit.com/products/613) from Adafruit, DS1307 Real Time Clock (https://www.adafruit.com/product/264) and MicroSD card breakout board (https://www.adafruit.com/products/254).

DS1307 is connected by I2C:
* SCL to analog 4
* SDA to analog 5

MicroSD is connected by SPI:
* CLK to digital 13
* DO to digital 12
* DI to digital 11
* CS to digital 10

Camera is connected to Serial:
* TX from camera to RX on Arduino
* RX from camera through 10K OM to TX on Arduino
* RX from camera through 10K OM to Ground.

Camera has motion detection and can take a snapshot at this time.
We use date and time information from DS1307 to know when we take a snapshot.
We create a directory with year and month in its name and use date, hour and minute for a filename.
We save our snapshots to a microSD cards.

