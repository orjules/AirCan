LogData <- read.table("./MPULogs/LOGS1.TXT",
                   header = TRUE,
                   sep = ",",
                   dec = ".")

LogData <- read.table("./MPULogs/LOGS4.TXT",
                      header = TRUE,
                      sep = ",",
                      dec = ".")

plot(x = 1,                 
     xlab = "Step", 
     ylab = "AccX, AccY, AccZ",
     xlim = c(0, 1550), 
     ylim = c(-40, 40),
     main = "Acceleration X,Y,Z",
     type = "n")
legend("topright", legend=c("AccX", "AccY", "AccZ"), 
       col=c("blue", "red", "green"), pch=c(1,1,1), cex=0.8)
lines(LogData$Step, LogData$AccX, col="blue")
lines(LogData$Step, LogData$AccY, col="red")
lines(LogData$Step, LogData$AccZ, col="green")


plot(x = 1,                 
     xlab = "Step", 
     ylab = "GyrX, GyrY, GyrZ",
     xlim = c(0, 1550), 
     ylim = c(-9, 9),
     main = "Gyro X,Y,Z",
     type = "n")
legend("topright", legend=c("GyrX", "GyrY", "GyrZ"), 
       col=c("blue", "red", "green"), pch=c(1,1,1), cex=0.8)
lines(LogData$Step, LogData$GyrX, col="blue")
lines(LogData$Step, LogData$GyrY, col="red")
lines(LogData$Step, LogData$GyrZ, col="green")

