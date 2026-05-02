N = 100

xs = 0:N

step = 1E-4
theta = seq(0, 1, by=step)

entropies = numeric(length(xs))
for(i in seq_along(xs))
{
    post = dbeta(theta, xs[i]+1, N-xs[i]+1)
    entropies[i] = -step*sum(post*log(post + 1E-300))
}

# Just the arithmetic mean because the prior predictive is 1/(N+1)
print(mean(entropies))
