dt=read.csv("err_50_1.csv")
View(dt)
df = subset(dt, select = -c(X) )
View(df)

dt2=read.csv("err2.csv")
dt2=as.data.frame(dt2)
View(dt2)
df2 = subset(dt2, select = -c(X) )
View(df2)

dt3=read.csv("err3.csv")
dt3=as.data.frame(dt3)
View(dt3)
df3 = subset(dt3, select = -c(X) )
View(df3)



par(mar = c(6, 6, 2, 2)) # Set the margin on all sides to 2
plot(df$Errors, ylab="Total error of neural network",
     xlab="Number of Iterations",cex.lab=1.25,cex.axis=1.15,pch=19)
points(df2$Errors, col="red")
points(df3$Errors, col="blue")
