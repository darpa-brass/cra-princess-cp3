optim.times <- read.csv("../../../kf-optim-times.csv", header=FALSE)
colnames(optim.times) <- c("trial", "time")

all.trials <- read.csv("../../../kf-results-combined.csv", header=FALSE)
colnames(all.trials) <- c("trial", "time", "method", "covar", "residual", "s1", "s2", "s3", "s4") 

library(plyr)
library(ggplot2)
library(zoo)
library(xtable)

smooth.trials <- ddply(all.trials, .(method, trial), function(df) {
  df <- df[order(df$time), ]
  df$ma <- rollmean(df$residual, 10, fill=NA)
  df$maxtime <- max(df$time)
  return(df)
})

trial.auc <- ddply(subset(smooth.trials, maxtime==299), .(trial, method), function(df) {
  f <- approxfun(df$time, df$residual, yleft=0, yright=0)
  auc <- integrate(f, lower=min(df$time) +1, upper=max(df$time) - 1, rel.tol=0.01, subdivisions=3000)
  return(data.frame(auc$value))
})
trial.auc.summ <- ddply(trial.auc, .(method), summarize, meanauc=mean(auc.value), sdauc=sd(auc.value))
trial.auc.summ$repr <- with(trial.auc.summ, paste0(round(meanauc, 2), " (", round(sdauc, 2), ")"))
print(xtable(trial.auc.summ[, c("method", "repr")]), include.rownames=FALSE)

g <- ggplot(subset(smooth.trials, maxtime==299 & !is.na(ma) & trial == "kf-results/kf-trial-4.txt"), aes(x=time, y=residual, color=method)) + 
  geom_line(alpha=0.5) + geom_hline(yintercept=5, color="blue") + geom_line(aes(y=ma), size=2) +
  #+ facet_wrap(~trial, scales="free_y") +
  labs(x="Time", y="Residual Metric") + scale_color_manual(name="Method", 
        breaks=c("nonadaptive", "princess"), labels=c("Non-adaptive", "PRINCESS"), values=c("black", 3)) + theme_bw(base_size=15) + theme(legend.position="top") +
    geom_vline(data=subset(optim.times, trial == "kf-results/kf-trial-4.txt"), aes(xintercept=time), color="red") + guides(color=guide_legend(ncol=3))
print(g)
pdf("../figures/kf-optimization-example.pdf", width=6, height=4)
print(g)
dev.off()

