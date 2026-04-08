# Digital-Clock

Embedded sistem za upravljanje digitalnim satom sa alarmom, podrškom za tastere, serijsku komunikaciju i LCD prikazom.

🔌 Ulazi / Izlazi
P0_0 – povećanje sati (trenutno vreme)
P0_1 – povećanje minuta (trenutno vreme)
P0_2 – povećanje sekundi (trenutno vreme)
P0_3 – povećanje sati (alarm)
P0_4 – povećanje minuta (alarm)
P0_5 – povećanje sekundi (alarm)
P0_6 – STOP (zaustavlja sat)
P0_7 – START (pokreće sat)
LCD (P1, P3) – prikaz vremena i alarma
UART – serijska komunikacija (slanje i prijem poruka)

⚙️ Funkcionalnosti
Prikaz trenutnog vremena u formatu: hh:mm:ss
Prikaz podešenog alarma
Podešavanje vremena i alarma preko tastera
Podešavanje vremena i alarma preko serijske komunikacije
START/STOP kontrola rada sata
Automatsko brojanje vremena pomoću tajmera
Slanje poruke kada se vreme poklopi sa alarmom

📡 Serijska komunikacija

Komunikacija se realizuje preko UART-a koristeći interni Baud Rate Generator.

Format poruke:
(T,hh,mm,ss) → podešavanje trenutnog vremena  
(A,hh,mm,ss) → podešavanje alarma

⏱️ Tajmeri
Timer2 – koristi se za merenje vremena (1 sekunda)
Generiše prekid i poziva:
time_tick() → povećava sekunde/minute/sate
proveru alarma

🧩 Moduli
time – logika vremena i alarma
display – upravljanje LCD displejem
serijska – UART komunikacija i parser
main – glavna petlja i obrada tastera

🔔 Alarm
Aktivira se kada se:
trenutno_vreme == alarm_vreme
Šalje poruku preko UART-a:
ALARM

🧠 Logika sistema

Prioritet rada:

STOP → PODEŠAVANJE → START → PRAĆENJE VREMENA → ALARM
