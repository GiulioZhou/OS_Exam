//Scrivere un programma cpinout che copi i dati letti dal file standard input nel file standard output e che:
//– al ricevimento del segnale SIGUSR1 indichi sul file standard error quanti byte sono stati copiati al momento attuale
//– mostri la propria attivita' sovrascrivendo un carattere (stampando –, \, |, / e poi ritornando a – per dare l'iimpressione
//di un'asta che gira.
//Provate il programma con un comando come:
//cat /dev/zero | ./cpinout | cat >/dev/null
//da un altro terminale poi mandate segnali con kill -USR1 xxxx, dove xxx e' il umero del processo cpinout

