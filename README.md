# MorseCodeRobotics

Meeskonnaliikmed: Erik Brück, Kristjan Sarv, Hannes Väster, Kaspar Merisalu

# Projekti Ülevaade:

Meie projekt hõlmab morse koodi saatja ja vastuvõtja loomist Arduino R4 mikrokontrolleri abil. Saatja kodeerib kasutaja sisestatud teksti morse koodiks ja edastab selle IR-signaalina. Vastuvõtja dekodeerib IR-signaali morse koodiks ja kuvab tõlgitud teksti LCD-ekraanil. Projekt on loodud robootika tunni raames neljaliikmelisele meeskonnale. Hetkel testitud pikim töötav vahemaa koodi saatmiseks on 6 meetrit.(Klassis ei olnud rohkem ruumi ja meie ülesehitus usb-toitega ei võimaldanud meil kaugemale testima minna).

Eesmärk: Kodeerida tekst morse koodiks ja edastada see IR-signaalina.
Vastuvõtjal dekodeerida IR-signaal ja kuvada tulemus LCD-ekraanil.

# Kasutatud Komponendid:

Arduino R4 WiFi: Mikrokontroller signaalitöötluseks.
IR LED: Signaali saatmiseks (tavaliselt 940 nm lainepikkusega).
IR-vastuvõtja (IR 1838): Signaali vastuvõtmiseks.
16x2 LCD-ekraan (I2C liidesega): Dekodeeritud teksti kuvamiseks.
Takistid: IR LED voolu piiramiseks(220 oomi).
Ühendusjuhtmed ja Breadboard: Komponentide ühendamiseks.
Toiteallikas: Arduino toiteks (USB).

# Tööpõhimõte:

### Saatja:
Kasutaja sisestab teksti arduino IDE Serial Monitori kaudu.
Arduino R4 kodeerib teksti morse koodiks, kasutades tähestiku ja morse koodi vastavustabelit.
Morse kood (punktid ja kriipsud) teisendatakse IR LED-i vilkumisteks (lühike si940 nm laisselülitus = punkt, pikk = kriips).

### Vastuvõtja:
IR-vastuvõtja tuvastab IR-signaalid ja mõõdab nende kestust.
Arduino R4 dekodeerib signaalid morse koodiks ja seejärel tekstiks.
Dekodeeritud tekst kuvatakse LCD-ekraanil.

# Tööprotsess ja Meeskonnatöö:

Planeerimine: Määratleti projekti eesmärgid ja jaotati ülesanded (nt elektroonika, programmeerimine, testimine).
Prototüüpimine: Ehitasime vooluringi Breadboardil ja testisime IR-signaale.
Programmeerimine: Kirjutasime koodi kahes osas (saatja ja vastuvõtja).
Testimine: Kontrollisime signaali edastust ja dekodeerimise täpsust.

Illustreerivad pildid skeemist on lisatud png failidena repositooriumi, saatja osa nimi on "Saatja" ja vastuvõtja oma "Vastuvõtja".
