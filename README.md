# CompConc-lab.4
O progama utiliza 4 threads para imprimir as seguintes mensagens:
"tudo bem?";
"bom dia!";
"até mais!";
"boa tarde!".

As threads que imprimem as duas primeiras mensagens devem executar antes das threads que executam as duas últimas.
Para garantir isso, é criada uma variável global 'count' que conta quantas threads já imprimiram suas mensagens. O valor de 'count' só é incrementado após a impressão de uma mensagem, e quando o valor da variável for maior ou igual a 2, as duas últimas mensagens podem ser impressas por suas threads.

Uma das threads designada a imprimir uma das duas primeiras mensagens, ao incrementar 'count' e deixa-la com o valor 2, manda um sinal para todas as outras threads (com a função pthread_cond_broadcast()) permitindo que possam imprimir suas mensagens.
