Sample usages
=============

(1) Esegue il deployment su tutto il gruppo "development", nell'ipotesi che
    l'utente che invoca lo script abbia accesso SSH password-less alla macchina remota


$ cd deployment
$ ansible-playbook -i hosts -v --limit development provision.yml


(2) Esegue il deployment sul singolo host, e fornisce le credenziali
    di autenticazione via linea comandi:

$ ansible-playbook -i hosts -vvvv --limit 192.168.15.112 --user=user -K -k provision.yml

