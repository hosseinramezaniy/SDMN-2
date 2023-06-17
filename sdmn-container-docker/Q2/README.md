# SDMN-Container-Docker : Q2 , Minimal implementation of Docker using C language
In this task we consider a container as a cloned process with new given namespaces which can be run with 3 arguments according to box below:
first we need compile cli.c file :

```
gcc cli.c -o prog
```
and after that we can run the program with desired restrictions :

```
sudo ./prog <new-hostname> <max-memory-volume> <max-number-of-pids>
```
at this stage a new shell will be open with the value we set above and other cgroup values will be written into the desired cgroup files and this writing process is done by the parent process in the first place.
It is noticable to say that the max number of processes in this container always should inserted above 5 otherwise the bash will not start.For testing a scenario we could insert the number 5 and try to enter the command below ofcourse after inserting the next part:
```
ls -l | ps fax
```
we should see the bash issuing an error for forking a new process because of that constraint we defined in the related cgroup.

## Using ps command  
To be able to use ps command we need first to insert the command below for mounting the proc directory :

```
mount -t proc proc /proc
```
## Testing namespaces 
For testing network namespace and its isolation , the command below should be entered : 
```
ip addr
```
To see how processes is running in this container or how they are placed in the process tree :
```
ps fax
```
note that we cannot cd back from this container with the following command
``` 
cd ..
```

