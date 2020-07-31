        if(strstr(buf, "subscan") || strstr(buf, "subscan"))
        {
        int port = 80;
        char *host = "api.c99.nl";
        char *key  = "961DY-6MXQ3-A0YD3-FSZOV";
        char *tool = "subdomainfinder";
        char InputAnswer[80];
        char HostOutput[80];
        char *user_input_host;

        sprintf(botnet, "Desired Host: ");
        if (send(azulafd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
        if (fdgets(InputAnswer, sizeof buf, azulafd) < 1) goto end;
        trim(InputAnswer);
        //user_input_host = ("%s", InputAnswer);
        char req[512];
        snprintf(req, sizeof(req), "GET /%s?key=%s&domain=%s HTTP/1.0\r\nHost: api.c99.nl\r\n\r\n", tool, key, InputAnswer);

        //char *req = {"GET /%s?key=%s&domain=%s HTTP/1.0\r\nHost: %s\r\n\r\n", tool, key, InputAnswer, host};
        struct hostent *server;
        struct sockaddr_in srv_addr;
        int sockfd, bytes, sent, received, total;
        char message[5000], response[20000];
        printf("User Input: %s\n", InputAnswer);

        printf("Request sent: %s\n", req);
    
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if ( sockfd < 0 ) {
            printf("Error opening socket!\n");
            exit(0);
        }
        server = gethostbyname(host);
        if ( server == NULL ) {
            printf("Error resolving hostname!\n");
            exit(0);
        }
        memset(&srv_addr,0,sizeof(srv_addr));
        srv_addr.sin_family = AF_INET;
        srv_addr.sin_port   = htons(port);
        memcpy(&srv_addr.sin_addr.s_addr,server->h_addr,server->h_length);
    
        if ( connect(sockfd,(struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0) {
            printf("Error connecting to host!\n");
            exit(0);
        }
    
        total = strlen(message);
        sent  = 0;
    
        do {
            bytes = write(sockfd, message+sent, total-sent);
            
            if ( bytes < 0 ) {
                printf("Error writing data to the socket!\n");
                exit(0);
            }
    
            if ( bytes == 0) {
                break;
            }
    
            received+=bytes;
        } while ( received < total );
        printf("Response: %s \r\n", response);
        if ( received == total ) {
            printf("Error storing response from socket!\n");
           // exit(0);
        }
        close(sockfd);
        //printf("Response: %s \r\n", response);
        }
