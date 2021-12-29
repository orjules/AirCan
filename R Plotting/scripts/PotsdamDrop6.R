Drop0 <- read.table("./MPULogs/PotsdamDropLogs/LOGS6.TXT",
                    header = TRUE,
                    sep = ",",
                    dec = ".")

plot(x = 1,                 
     xlab = "Step", 
     ylab = "AccX, AccY, AccZ",
     xlim = c(1000, 1400), 
     ylim = c(-80, 80),
     main = "Acceleration X,Y,Z",
     type = "n")
legend("topright", legend=c("AccX", "AccY", "AccZ"), 
       col=c("blue", "red", "green"), pch=c(1,1,1), cex=0.8)
lines(Drop0$Step, Drop0$AccX, col="blue")
lines(Drop0$Step, Drop0$AccY, col="red")
lines(Drop0$Step, Drop0$AccZ, col="green")

plot(x = 1,                 
     xlab = "Step", 
     ylab = "GyrX, GyrY, GyrZ",
     xlim = c(1000, 1400), 
     ylim = c(-10, 10),
     main = "Gyro X,Y,Z",
     type = "n")
legend("topright", legend=c("GyrX", "GyrY", "GyrZ"), 
       col=c("blue", "red", "green"), pch=c(1,1,1), cex=0.8)
lines(Drop0$Step, Drop0$GyrX, col="blue")
lines(Drop0$Step, Drop0$GyrY, col="red")
lines(Drop0$Step, Drop0$GyrZ, col="green")


# Ganzer Ablauf
plot(x = 1,                 
     xlab = "Step", 
     ylab = "AccX, AccY, AccZ in g",
     xlim = c(0, 4000), 
     ylim = c(-80, 80),
     main = "Acceleration Test 6",
     type = "n")
legend("topright", legend=c("AccX", "AccY", "AccZ"), 
       col=c("blue", "red", "green"), pch=c(1,1,1), cex=0.8)
lines(Drop0$Step, Drop0$AccX, col="blue")
lines(Drop0$Step, Drop0$AccY, col="red")
lines(Drop0$Step, Drop0$AccZ, col="green")

plot(x = 1,                 
     xlab = "Step", 
     ylab = "GyrX, GyrY, GyrZ in deg/s",
     xlim = c(0, 4000), 
     ylim = c(-10, 10),
     main = "Gyro X,Y,Z",
     type = "n")
legend("topright", legend=c("GyrX", "GyrY", "GyrZ"), 
       col=c("blue", "red", "green"), pch=c(1,1,1), cex=0.8)
lines(Drop0$Step, Drop0$GyrX, col="blue")
lines(Drop0$Step, Drop0$GyrY, col="red")
lines(Drop0$Step, Drop0$GyrZ, col="green")
