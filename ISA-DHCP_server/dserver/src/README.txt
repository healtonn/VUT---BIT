Autor programu: Jakub Jochl�k
Login: xjochl00

Popis: Aplikace dserver slou�� jako jednoduch� DHCP server. Pro jeho spu�t�n� je zapot�eb� root pr�va. Jednotliv� parametry jsou:
Povinn�:
-p s parametrem ur�uj�c� pods� form�tu <ip_addresa/maska>.
Voliteln�:
-e slou�� k v��tu jednotliv�ch adres, kter� se nebudou p�id�lovat, formou <ip_addresa>,<ip_addresa>,<ip_addresa>,...
-h vyp�e n�pov�du

Pou�it�: sudo ./dserver -p 192.168.0.0/24 [-e 192.168.0.1,192.168.0.2][-h]
Konkretni p��kad: sudo ./dserver -p 192.168.0.0/24 -e 192.168.0.1,192.168.0.2,192.168.0.3

Program spl�uje z�kladn� zad�n� + je implementovan� unicast roz���en�

Seznam soubor�:
	Makefile		- prekladov� dokument
	manual.pdf		- dokumentace
	README			- tento dokument
	dserver.cpp		- zdrojovy kod projektu
	dserver.h		- hlavi�kov� soubor k projektu
	parameters.cpp		- Soubor pro spracovani vstupn�ch parametr�
	parameters.h		- hlavi�kov� soubor pro spracov�n� parametr�
	dhcpMessage.h		- hlavi�kov� soubor obsahuj�c� strukturu pro uchov�v�n� DHCP informace