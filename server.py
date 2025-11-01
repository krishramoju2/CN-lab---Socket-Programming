import socket

def start_server():
    host = '127.0.0.1'
    port = 8080

    # Create socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)

    print(f"Server listening on {host}:{port}...")
    conn, addr = server_socket.accept()
    print(f"Client connected from {addr}")

    while True:
        data = conn.recv(1024).decode()
        if not data:
            break
        if data.lower().startswith("exit"):
            print("Client disconnected.")
            break

        print(f"Client: {data.strip()}")

        msg = input("Server: ")
        conn.send(msg.encode())

        if msg.lower().startswith("exit"):
            print("Server exiting...")
            break

    conn.close()
    server_socket.close()

if __name__ == "__main__":
    start_server()
