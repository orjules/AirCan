LogData <- read.table("./MPULogs/LOGS1.TXT",
                   header = TRUE,
                   sep = ",",
                   dec = ".")

plot(x = 1,                 
     xlab = "Step", 
     ylab = "AccX, AccY, AccZ",
     xlim = c(0, 1200), 
     ylim = c(-20, 20),
     main = "Accelaratoin X,Y,Z",
     type = "n")
points(LogData$Step, LogData$AccX, col="blue")
points(LogData$Step, LogData$AccY, col="red")
points(LogData$Step, LogData$AccZ, col="green")

plot(x = 1,                 
     xlab = "Step", 
     ylab = "GyrX, GyrY, GyrZ",
     xlim = c(0, 1200), 
     ylim = c(-10, 10),
     main = "Gyro X,Y,Z",
     type = "n")
points(LogData$Step, LogData$GyrX, col="blue")
points(LogData$Step, LogData$GyrY, col="red")
points(LogData$Step, LogData$GyrZ, col="green")
