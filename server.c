#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/*int factorielle(int n) {
    if (n == 0) {
        return 1;
    }
    else {
        return n * factorielle(n-1);
    }
}
*/
int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    int client_address_length = sizeof(client_address);
    char buffer[1024] = {0};

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Erreur de création de socket");
        exit(EXIT_FAILURE);
    }
    printf("[**] Socket de serveur créée avec succès.\n");

    // Bind socket to address and port
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(5000);
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Erreur de liaison de socket");
        exit(EXIT_FAILURE);
    }
    printf("[**] Socket de serveur liée avec succès.\n");

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Erreur d'écoute de socket");
        exit(EXIT_FAILURE);
    }
    printf("[**] Serveur en écoute sur le port %d...\n", 5000);

    // Accept incoming connection
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t*)&client_address_length);
    if (client_socket < 0) {
        perror("Erreur d'acceptation de socket");
        exit(EXIT_FAILURE);
    }
    printf("[**] Connexion acceptée avec succès.\n");

    // Receive integer from client
   /* int n;
    if (read(client_socket, &n, sizeof(int)) < 0) {
        perror("Erreur de lecture de socket");
        exit(EXIT_FAILURE);
    }
    printf("Message reçu du client : %s\n", &n);

    // Calculate factorial and send result to client
    int result = factorielle(n);
    if (write(client_socket, &result, sizeof(int)) < 0) {
        perror("Erreur d'écriture de socket");
        exit(EXIT_FAILURE);
    }*/
    FILE *image = fopen("./receive.png", "wb");
    while (1) {
        ssize_t bytesRead = recv(client_socket, buffer, 1024, 0);
        if (bytesRead < 1) break;
        fwrite(buffer, 1, bytesRead, image);
    }
// Close the image file and socket
fclose(image);
close(client_socket);
    // Close sockets
close(server_socket);

    return 0;
}
