library(ggplot2)
library(plyr)
library(class)
library(gridExtra)
library(grid)

set.seed(1)
nsamples <- 100

gen.points <- function(xmean, coeff, xsd, ysd, color, b0=0) {
  x <- rnorm(nsamples, mean=xmean, sd=xsd)
  y <- rnorm(nsamples, mean=x*coeff + b0, sd=ysd)
  data.frame(x=x, y, z=x*y-x+rnorm(nsamples, mean=0, sd=0.1), color=color)
}

all.points <- rbind(gen.points(2, 2, 0.3, 0.3, "2"),
                    gen.points(4, 1, 0.5, 0.3, "3"),
                    gen.points(2, 1, 0.5, 0.5, "4", b0=-1),
                    gen.points(3.5, 1, 0.3, 0.3, "5", b0=-1.5))

kmeans.results <- kmeans(as.matrix(all.points[, c("x", "y")]), 4)
cluster.means <- laply(split(all.points, kmeans.results$cluster), function(v) mean(v$z))

grid <- cbind(expand.grid(list(x=seq(0, 5, length=400), 
                         y=seq(0, 5, length=400))))
grid$z <- knn(kmeans.results$centers, grid, cl=factor(cluster.means))
grid$actz <- with(grid, x*y - x)
g1 <- ggplot(all.points, aes(x=x, y=y)) + 
  geom_raster(data=grid, aes(fill=as.numeric(as.character(z))), interpolate=TRUE) + 
  geom_point(data=grid, aes(fill=grid$actz), alpha=0) +
  scale_fill_continuous(name=expression(m(x))) + theme_bw(base_size=15) + 
  labs(x=expression(x[1]), y=expression(x[2])) +
  scale_y_continuous(expand = c(0,0), lim=c(0, 5)) + scale_x_continuous(expand = c(0,0), lim=c(0, 5)) +
  geom_point(color="white")
g2 <- ggplot() + geom_raster(data=grid, aes(x=x, y=y, fill=actz), interpolate=TRUE) + 
  scale_fill_continuous(name=expression(y)) + theme_bw(base_size=15) + 
  labs(x=expression(x[1]), y=expression(x[2])) +
  scale_y_continuous(expand = c(0,0)) + scale_x_continuous(expand = c(0,0))
g <- grid.arrange(g1, g2)#, main = textGrob(title, gp = gpar(fontsize = 20)), ncol = 2)
print(g)

pdf("../figures/mean-function-example.pdf", width=8, height=7.4)
g <- arrangeGrob(g1, g2)
grid.draw(g)
dev.off()
