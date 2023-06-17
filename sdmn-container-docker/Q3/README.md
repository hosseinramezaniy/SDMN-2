# SDMN-Container-Docker : Q3 , Dockerizing a http server 
To build the image and offloading it on a mirror server, insert the following comand :

```
docker build -t my_dear_httpserver:1.0 .
```
## Running the image 

To run the server/container run the command below :

```
docker run -p 8000:8000 my_dear_httpserver:1.0
```
## Testing the HTTP server
After running the server , check out the IP address of docker0 interface and curl it as the following commands :

### for GET request 
```
curl docker0_IP_address:8000  
```
### for POST request 
```
curl docker0_IP_address:8000 -X POST
```



