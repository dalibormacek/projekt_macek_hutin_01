# Projekt Chýtrá domácnost
## **Úvod**
Tato dokumentace popisuje implementaci ovládání osvětlení v chytré domácnosti pomocí ESP32 mikrokontroleru a mobilního zařízení. Projekt umožňuje uživatelům zapínat a vypínat světla v domácnosti prostřednictvím mobilní aplikace, která komunikuje s ESP32 pomocí MQTT protokolu. Také je vybavena termostatem, dokáže měřit teplo a vlhkost v domě a také můžeme pomocí chytré domácnosti i teplotu nastavovat. Má také senzor pohybu, který posílá notifikace na telefon pokaždé, když senzor zaznamená pohyb v domě při nepřítomnosti majitele.
## **Součástky**
- ESP32

- OLED displej

- Relé modul

- Termostatický senzor (DHT11) 

- Rotační enkodér

- PIR senzor pohybu (AM312)

## Popis jednotlivých součástek
**ESP32** - je to výkonný mikrokontroler s Wi-Fi a Bluetooth funkcemi, který se používá pro různé aplikace v oblasti IoT, například chytrá domácnost, na kterou to využijeme.

**OLED display** - je typ displeje, který využívá organické polymery pro vytváření světelných pixelů a je často používán s ESP32 pro zobrazování dat a textu v projektech IoT.

**Relé modul** - je typ displeje, který využívá organické polymery pro vytváření světelných pixelů a je často používán s ESP32 pro zobrazování dat a textu v projektech IoT.

**Termostatický senzor (DHT11)** - je digitální senzor, který měří teplotu a vlhkost vzduchu v okolí. Jedná se o levný a populární senzor vhodný pro různé projekty.

**Rotační enkodér** - je zařízení používané k detekci směru a rychlosti otáčení objektu, jako je například knoflík nebo kolo.

**PIR senzor pohybu (AM312)** - je zařízení, které detekuje pohyb v okolí pomocí infračerveného záření, což ho činí ideální volbou pro různé bezpečnostní a automatizační aplikace.

## Jak by to mělo fungovat
**Programování ESP32** - ESP32 je naprogramováno pro připojení k WiFi a komunikaci s MQTT brokerem. Připojilo by se k domácí WiFi síti. Nastavilo by se připojení k MQTT brokeru (adresa, port, přihlašovací údaje). Vytvořil by se MQTT klient pro komunikaci s mobilním zařízením.

**Ovládání osvětlení** - Nastavila by se funkce pro zapínání a vypínání osvětlení pomocí relé modulu. Přijímal zprávy z mobilní aplikace přes MQTT a reagoval na ně podle požadavků uživatele.

**Termostat** - Data by se získávala z teplotního a vlhkostního senzoru. Dále by algoritmus porovnával naměřenou teplotu s nastavenou teplotou. Kde by se odesílali aktuální teplotní hodnoty a notifikace v případě potřeby by byla možná regulace teploty.

**Senzor pohybu** - Periodicky by se četl stav senzoru pohybu. Odesílala by notifikace na mobilní zařízení v případě detekce pohybu v místnosti při nepřítomnosti majitele.

**Ovládací jednotka** - Fyzické ovládání chytré domácnosti slouží jako centrální kontrolní prvek pro správu a manipulaci s různými aspekty chytré domácnosti.

Jeho hlavní funkce zahrnují:
- Ovládání osvětlení
- Řízení teploty
- Správa bezpečnostních zařízení
- Zobrazení času
## Zhrnutí
Chytrá domácnost by se skládala z ESP32, PIR senzoru pohybu, termostatického senzoru DHT11, relé modulu a MQTT brokeru. ESP32 by byl programován k připojení k domácí Wi-Fi síti a komunikaci s MQTT brokerem. Přes MQTT by bylo možné ovládat osvětlení a termostat, a také přijímat notifikace z PIR senzoru pohybu. Vaše mobilní zařízení by bylo vybaveno aplikací, která by komunikovala s ESP32 přes MQTT, umožňující ovládání osvětlení a termostatu, a zobrazovala notifikace o detekci pohybu. To vše by umožnilo efektivní a pohodlnou automatizaci domácnosti, kterou lze ovládat vzdáleně.







