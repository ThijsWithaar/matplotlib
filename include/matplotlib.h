/*
Thin wrapper around python's matplotlib, to allow plotting from C++

based on:
	https://github.com/lava/matplotlib-cpp/blob/master/matplotlibcpp.h

This one is with pybind11 to reduce boilerplate code
*/
#pragma once

#include <array>
#include <map>
#include <memory>

#include <Eigen/Dense>


typedef std::map<std::string, std::string> options_t;


class Figure
{
public:
	struct Impl;

	Figure(std::unique_ptr<Impl>&& m);
	~Figure();
	Figure(const Figure& o);

	void add_subplot(int nrows, int ncols, int index, const options_t& opt={});

	void tight_layout();

private:
	std::unique_ptr<Impl> m;
};

class MatplotLib
{
public:
	typedef Eigen::Ref<Eigen::ArrayXd> vecin_t;

	MatplotLib(std::string backend="agg");
	~MatplotLib();

	Figure figure(int nr=1, std::array<double,2> size = {0,0});

	void plot(vecin_t x, vecin_t y, const options_t& options = {});

	void plot(vecin_t x, vecin_t y, std::string style = "", const options_t& options = {});

	void semilogx(vecin_t x, vecin_t y, const options_t& options = {});

	void semilogy(vecin_t x, vecin_t y, const options_t& options = {});

	void loglog(vecin_t x, vecin_t y, const options_t& options = {});

	void imshow(Eigen::Ref<Eigen::MatrixXd> I, const options_t& options = {});

	void colorbar();

	void xlabel(std::string l);

	void ylabel(std::string l);

	void legend();

	void title(std::string t);

	std::array<double, 2> xlim();

	void xlim(double left, double right);

	std::array<double, 2> ylim();

	void ylim(double bottom, double top);

	void savefig(std::string fname);

	void xkcd();

	void show();

private:
	struct Impl;
	std::unique_ptr<Impl> m;
};
