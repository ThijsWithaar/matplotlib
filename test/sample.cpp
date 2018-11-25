#include <iostream>

#include <Eigen/Dense>

#include <matplotlib.h>


int main(int, char*[])
try
{
	Eigen::ArrayXd x = Eigen::ArrayXd::LinSpaced(20, 0, 4);
	Eigen::ArrayXd y = x.sin();
	Eigen::ArrayXd z = x.cos();

	Eigen::MatrixXd I(10, 10);
	for(int r=0; r < I.rows(); r++)
		for(int c=0; c < I.cols(); c++)
			I(r,c) = std::sin(r*.1) * c;

	// Initialize plotting
	MatplotLib p("Qt5Cairo");
	auto f = p.figure(2);

	// 2D plot
	f.add_subplot(1,2,1);
	p.plot(x, z, {{"label","cosinus"}});
	p.plot(x, y, "m:", {{"label","sinus"}});
	p.legend();
	p.xlabel("Horizontal");
	p.ylabel("Vertical");
	p.title("It's a title");

	// 2D image
	f.add_subplot(1,2,2);
	p.imshow(I, {
		{"interpolation","nearest"},
		{"cmap","gray"}
	});
	p.colorbar();

	f.tight_layout();
	p.savefig("tensorplot.pdf");

	p.show();
	return 0;
}
catch(std::exception& e)
{
	std::cout << e.what() << "\n";
	return -1;
}
