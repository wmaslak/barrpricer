#' Plot some sample paths 
#'
#' @param nint number of points on path
#' @param strike strike price
#' @param spot spot price at pricing moment
#' @param barrier continuous barrier
#' @param vol volatility
#' @param rf risk free rate
#' @param maturity time to maturity in years
#' @param nreps number of paths to generate

plot_sample_paths <- function(nint,strike,spot,barrier,vol,rf,maturity,nreps=20){
paths <- getBarrierPaths(min(nint,100),strike,spot,barrier,vol,rf,maturity,nReps = min(nreps,100))
# dim(paths) <- c(nreps,nint)
paths %>%
  as.data.frame() %>% 
  mutate(t=c(1:nint)) %>% 
  pivot_longer(-t) %>% 
  ggplot()+
  geom_line(aes(x=t,y=value,color=name))+
  theme(legend.position = "none")+
  geom_abline(aes(intercept = barrier,slope=0),
              col = "red",
              linetype = "dashed",
              size=1)+
  geom_abline(aes(intercept = strike,slope=0),
              col = "black",
              linetype = "solid",
              size=1)+
  scale_x_discrete()+
  xlab("time")+
  ylab("price (S)")

}
