# Mini Twitter
Mini Twitter jest jednym z moich projektów zaliczeniowych na przedmiot Sieci komputerowe.
Mini Twitter składa sie z programów klienta i serwera realizujące mini serwis ,,Twitter 2.0'' za pomocą pamięci dzielonej Systemu V

Mój program zawiera 2 pliki:<br /> 
1)Serwer: 
Uruchamiany jest z dwoma parametrami: nazwa pliku (służącą do generowania klucza IPC, System V) oraz liczba całkowita n oznaczająca maksymalną liczbę wiadomości
Serwer tworzy klucz IPC na podstawie nazwy podanej jako argument powyżej i korzystając z powyższego klucza (lub nazwy) tworzy segment pamięci dzielonej zawierający n rekordów (,,slotów'') do przechowywania wpisów. Dodatkowo, każdy rekord w serwisie zawiera nazwę użytkownika klienta i jego wpis oraz liczbę polubień
Serwer czeka na sygnały od użytkownika:
Ctrl^Z powoduje wypisanie aktualnej zawartości serwisu na ekran (tylko niepuste wpisy) jak w poniższych przykładach;
Ctrl^C powoduje zakończenie pracy serwera (poprzedzone ,,posprzątaniem''). 
 
2)Klient:
Uruchamiany  z dwoma parametrami: nazwa pliku (służąca do identyfikacji obiektu IPC lub jego klucza), nazwa użytkownika (pod tą nazwą będzie widniał jego wpis w serwisie). 
Klint dołącza uprzednio utworzony przez serwer segment pamięci dzielonej zawierający wpisy i wyświetla wszystkie wiadomości, polubienia oraz informację ile jest jeszcze wolnych slotów w serwisie.
Następnie pyta o typ akcji: nowy wpis lub polubienia użytkownik wpisuje odpowiednio 'N' lub 'n' albo 'L' 'l':
W przpadku dodawania nowego wpisu, jeżeli w serwisie nie ma już wolnego miejsca to informuje o tym użytkownika i kończy pracę.
Natomiast jeśli jeszcze jest wolne miejsce w serwisie to pyta użytkownika o komunikat a następnie wpisuje ten komunikat w pierwsze wolne miejsce w serwisie łącznie z numerem postu i nazwą użytkownika. 
W przypadku polubienia program pyta o numer wpisu.
Jeśli wpis o tym numerze nie istnieje informuje o tym użytkownika i kończy pracę;
jeśli taki wpis istnieje zwiększa jego licznik polubień o 1.

Między klientem, a serwerem jest przekazywana struktura my_data, w której przechowuję:
  int typ - informacja o tym czy istnieją już jakies posty,
  char txt[MY_MSG_SIZE] - zawartosc posta ("tweet"),
  int likes - ilość lików pod postem,
  char user[16] - nazwa użytkownika dodającego post,
  int nr - numer posta,
  int max - maksymalna ilosc postow

# Co mogę dodać 
1) dostęp synchronizowany poprzez semafory
2) połączenie pomiędzy hostami (korzystanie z UDP?)

# Czego się nauczyłam
Nauczyłam się, a raczej nadal się uczę jakie zadanie powinien spełniać prosty program klient-serwer, jako że jest to moj pierwsze zadanie tego typu.
Projekt pomógł mi również zrozumieć działanie pamięci współdzielonej w IPC System V
