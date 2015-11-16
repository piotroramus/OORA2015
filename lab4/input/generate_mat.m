n = 1000;
A = random_cov(n);

output_file = sprintf('matrix_%dx%d.txt', n, n); 
dlmwrite(output_file, A);