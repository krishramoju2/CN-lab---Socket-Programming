import socket

def start_client():
    host = '127.0.0.1'
    port = 8080

    # Create socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, port))
    print(f"Connected to server {host}:{port}")

    while True:
        msg = input("Client: ")
        client_socket.send(msg.encode())

        if msg.lower().startswith("exit"):
            print("Client exiting...")
            break

        data = client_socket.recv(1024).decode()
        print(f"Server: {data.strip()}")

        if data.lower().startswith("exit"):
            print("Server closed the connection.")
            break

    client_socket.close()

if __name__ == "__main__":
    start_client()
