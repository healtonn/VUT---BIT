Autor programu: Jakub Jochlík
Login: xjochl00

Popis: Aplikace dserver slouí jako jednoduchı DHCP server. Pro jeho spuštìní je zapotøebí root práva. Jednotlivé parametry jsou:
Povinné:
-p s parametrem urèující podsí formátu <ip_addresa/maska>.
Volitelné:
-e slouí k vıètu jednotlivıch adres, které se nebudou pøidìlovat, formou <ip_addresa>,<ip_addresa>,<ip_addresa>,...
-h vypíše nápovìdu

Pouití: sudo ./dserver -p 192.168.0.0/24 [-e 192.168.0.1,192.168.0.2][-h]
Konkretni pøíkad: sudo ./dserver -p 192.168.0.0/24 -e 192.168.0.1,192.168.0.2,192.168.0.3

Program splòuje základní zadání + je implementované unicast rozšíøení

Seznam souborù:
	Makefile		- prekladovı dokument
	manual.pdf		- dokumentace
	README			- tento dokument
	dserver.cpp		- zdrojovy kod projektu
	dserver.h		- hlavièkovı soubor k projektu
	parameters.cpp		- Soubor pro spracovani vstupních parametrù
	parameters.h		- hlavièkovı soubor pro spracování parametrù
	dhcpMessage.h		- hlavièkovı soubor obsahující strukturu pro uchovávání DHCP informace