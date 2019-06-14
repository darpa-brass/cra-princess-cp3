optim.times <- read.csv("../../../pg-optim-times.csv", header=FALSE)
colnames(optim.times) <- c("trial", "time")

all.trials <- read.csv("../../../pg-results-combined.csv", header=FALSE)
colnames(all.trials) <- c("trial", "time", "method", "runtime", "diskaccess", "s1", "s2")
trial.max.time <- ddply(all.trials, .(method, trial), summarize, max.time=max(time))
all.trials <- merge(all.trials, trial.max.time)
all.trials <- subset(all.trials, max.time==299)

library(plyr)
library(ggplot2)
library(zoo)
library(xtable)


smooth.trials <- ddply(all.trials, .(method, trial), function(df) {
  df <- df[order(df$time), ]
  df$ma <- rollmean(df$runtime, 10, fill=NA)
  return(df)
})

baseline.recs <- subset(smooth.trials, method == "nonadaptive")
relative.trials <- merge(smooth.trials, baseline.recs[, c("trial", "time", "runtime")], by=c("trial", "time"), suffixes=c("", ".baseline"))
relative.trials$rel.runtime <- relative.trials$runtime / relative.trials$runtime.baseline

trial.auc <- ddply(smooth.trials, .(trial, method), function(df) {
  f <- approxfun(df$time, df$runtime, yleft=0, yright=0)
  auc <- integrate(f, lower=min(df$time) +1, upper=max(df$time) - 1, rel.tol=0.01, subdivisions=3000)
  return(data.frame(auc$value))
})

trial.auc.summ <- ddply(trial.auc, .(method), summarize, meanauc=mean(auc.value), sdauc=sd(auc.value))
trial.auc.summ$repr <- with(trial.auc.summ, paste0(round(meanauc, 2), " (", round(sdauc, 2), ")"))
print(xtable(trial.auc.summ[, c("method", "repr")]), include.rownames=FALSE)

g <- ggplot(subset(relative.trials, method == "princess"), aes(x=rel.runtime)) + 
  geom_histogram(fill=2, alpha=0.5, binwidth=0.1) + coord_cartesian(xlim=c(0, 2)) + 
  theme_bw(base_size=16) + labs(x="Relative Runtime", y="Count")
print(g)
pdf("../figures/pg-relative-performance.pdf", width=6, height=4)
print(g)
dev.off()
