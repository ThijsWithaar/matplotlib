#include <matplotlib.h>

#include <iostream>

#include <pybind11/embed.h>
#include <pybind11/eigen.h>


namespace py = pybind11;


py::kwargs asKwargs(const options_t& kv)
{
	py::kwargs kw;
	for(const auto& k: kv)
		kw[py::cast(k.first)] = k.second;
	return kw;
}


//-- Figure


struct Figure::Impl
{
	Impl(py::object f):
		f(f)
	{
	}

	py::object f;
};

Figure::Figure(std::unique_ptr<Impl>&& m):
	m(std::move(m))
{
}

Figure::Figure(const Figure& o):
	m(std::make_unique<Impl>(o.m->f))
{
}

Figure::~Figure()
{
}


void Figure::add_subplot(int nrows, int ncols, int index, const options_t& opt)
{
	auto kw = asKwargs(opt);
	m->f.attr("add_subplot")(nrows, ncols, index, **kw);
}


void Figure::tight_layout()
{
	m->f.attr("tight_layout")();
}


//-- Matplotlib


struct MatplotLib::Impl
{
	Impl(std::string backend);

	py::scoped_interpreter ip;
	py::module mpl;
	py::module pp;
};

MatplotLib::Impl::Impl(std::string backend)
{
	mpl = py::module::import("matplotlib");
	if(!backend.empty())
		mpl.attr("use")(backend);	// Need something without an event loop
	pp = py::module::import("matplotlib.pyplot");
}

MatplotLib::MatplotLib(std::string backend):
	m(std::make_unique<Impl>(backend))
{
}

MatplotLib::~MatplotLib()
{
}

Figure MatplotLib::figure(int nr, std::array<double,2> size)
{
	py::object figure = m->pp.attr("figure");

	py::object handle;
	if(size[0] > 0)
	{
		py::kwargs kw;
		kw["figsize"] = pybind11::make_tuple(size[0], size[1]);
		handle = figure(nr, **kw);
	}
	else
	{
		handle = figure(nr);
	}

	return Figure(std::make_unique<Figure::Impl>(handle));
}

void MatplotLib::plot(vecin_t x, vecin_t y, const options_t& options)
{
	plot(x, y, "", options);
}

void MatplotLib::plot(vecin_t x, vecin_t y, std::string style, const options_t& options)
{
	auto kw = asKwargs(options);
	if(style.empty())
		m->pp.attr("plot")(x, y, **kw);
	else
		m->pp.attr("plot")(x, y, style, **kw);
}

void MatplotLib::semilogx(vecin_t x, vecin_t y, const options_t& options)
{
	auto kw = asKwargs(options);
	m->pp.attr("semilogx")(x, y, **kw);
}

void MatplotLib::semilogy(vecin_t x, vecin_t y, const options_t& options)
{
	auto kw = asKwargs(options);
	m->pp.attr("semilogy")(x, y, **kw);
}

void MatplotLib::loglog(vecin_t x, vecin_t y, const options_t& options)
{
	auto kw = asKwargs(options);
	m->pp.attr("loglog")(x, y, **kw);
}

void MatplotLib::imshow(Eigen::Ref<Eigen::MatrixXd> I, const options_t& options)
{
	auto kw = asKwargs(options);
	m->pp.attr("imshow")(I, **kw);
}

void MatplotLib::colorbar()
{
	m->pp.attr("colorbar")();
}

void MatplotLib::xlabel(std::string l)
{
	m->pp.attr("xlabel")(l);
}

void MatplotLib::ylabel(std::string l)
{
	m->pp.attr("ylabel")(l);
}

void MatplotLib::legend()
{
	m->pp.attr("legend")();
}

void MatplotLib::title(std::string t)
{
	m->pp.attr("title")(t);
}

std::array<double, 2> MatplotLib::xlim()
{
	py::tuple lm = m->pp.attr("xlim")();
	return std::array<double, 2>{lm[0].cast<double>(), lm[1].cast<double>()};
}

void MatplotLib::xlim(double left, double right)
{
	m->pp.attr("xlim")(left, right);
}

std::array<double, 2> MatplotLib::ylim()
{
	py::tuple lm = m->pp.attr("ylim")();
	return std::array<double, 2>{lm[0].cast<double>(), lm[1].cast<double>()};
}

void MatplotLib::ylim(double bottom, double top)
{
	m->pp.attr("ylim")(bottom, top);
}

void MatplotLib::savefig(std::string fname)
{
	m->pp.attr("savefig")(fname);
}

void MatplotLib::xkcd()
{
	m->pp.attr("xkcd")();
}

void MatplotLib::show()
{
	m->pp.attr("show")();
}
