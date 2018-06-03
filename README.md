# transponder
GPS data sending through an audio channel

This short code utilises the PPMPWM and FSKModem libraries.
The serial line is a GPS serial in from the Arkbird FC
selecting every second GPPGA NMEA sentences to send it as an audio FSK signal

The RC receiver has a PPM output, so I have to convert it to PPM for Arkbird
