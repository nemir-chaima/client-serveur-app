#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};
    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Erreur de création de socket");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(5000);
    printf(" \n");
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Erreur de connexion de socket");
        exit(EXIT_FAILURE);
    }
// calcule de la factorielle : 
   /* // Send integer to server
    int n;
    printf("[**] Entrez un entier pour calculer sa factorielle : ");
    scanf("%d", &n);
    if (write(client_socket, &n, sizeof(int)) < 0) {
        perror("Erreur d'écriture de socket");
            exit(EXIT_FAILURE);
    }

    // Receive result from server
    int result;
    if (read(client_socket, &result, sizeof(int)) < 0) {
        perror("Erreur de lecture de socket");
        exit(EXIT_FAILURE);
    }

    // Print result
    printf("[**] Le résultat est : %d\n", result);
*/
// open the file image
    FILE *image = fopen("/home/chanez/documents/client_server/game.png", "r");
    if (!image) {
        printf("Image file error\n");
        return -1;
    }

    // Read the image file into a buffer and send over socket
    while (!feof(image)) {
        size_t bytesRead = fread(buffer, 1, 1024, image);
        if (bytesRead < 1) break;
        send(client_socket, buffer, bytesRead, 0);
    }
    // Close the image file and socket
    fclose(image);
    // Close socket
    close(client_socket);

    return 0;
}
