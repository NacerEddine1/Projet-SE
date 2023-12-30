projet système d'exploitation

q1: Quelles sont les structures de données à utiliser ?
1.Matrices B,C,A:
Int B[n1][m1];
Int B[n1][m1];
Int B[n1][m1];
2.Tampon T:
Int T[N];
3.Mutex et Semaphore:
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

q2: Comment allez-vous protéger l'accès à ces données?
Pour protéger l'accès aux données partagées entre les threads
Matrices B,C,A:
pthread_mutex_lock(&mutex);
// Accès à la matrice B
// ...
pthread_mutex_unlock(&mutex);
Tampon T:
pthread_mutex_lock(&mutex);
// Accès au tampon T
// ...
pthread_mutex_unlock(&mutex);

q3: quels sont les risques?
Conditions de concurrence : Les threads producteurs et consommateurs peuvent accéder simultanément aux données partagées, entraînant des conditions de concurrence. Cela peut conduire à des résultats imprévisibles si les opérations ne sont pas correctement synchronisées.
Blocage: Des situations de blocage peuvent se produire si un thread attend une ressource détenue par un autre thread, et vice versa. Cela peut se produire si la synchronisation entre les threads n'est pas correctement gérée.
Problèmes de performance : Une mauvaise gestion des threads et de la synchronisation peut entraîner des problèmes de performance, tels que des temps d'attente excessifs ou une utilisation inefficace des ressources du processeur.
Erreurs de programmation : Des erreurs de programmation, telles que des accès incorrects à la mémoire partagée ou des index hors limites, peuvent provoquer des comportements inattendus et des plantages du programme.
Taille du tampon insuffisante: Si la taille du tampon est trop petite, les producteurs et les consommateurs peuvent se bloquer mutuellement, entraînant un ralentissement du processus global.
