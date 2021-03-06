// Created 07-Apr-2012 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef BAOFIT_ABS_CORRELATION_MODEL
#define BAOFIT_ABS_CORRELATION_MODEL

#include "likely/FitModel.h"

#include "cosmo/types.h"

#include <string>
#include <vector>

namespace baofit {
	class AbsCorrelationModel : public likely::FitModel {
	// Represents an abstract parameterized model of a two-point correlation function.
	public:
	    // Creates a new model with the specified name.
		AbsCorrelationModel(std::string const &name);
		virtual ~AbsCorrelationModel();
		// Returns the correlation function evaluated in redshift space where (r,mu) is
		// the pair separation and z is their average redshift. The separation r should
		// be provided in Mpc/h. Updates our current parameter values.
        double evaluate(double r, double mu, double z, likely::Parameters const &params);
        // Returns the correlation function for the specified multipole at co-moving pair separation
        // r and average pair redshift z. Updates our current parameter values.
        double evaluate(double r, cosmo::Multipole multipole, double z, likely::Parameters const &params);
        // Returns the -log(prior-likelihood) for the specified parameter values. The default
        // implementation returns zero, which corresponds to no priors on any parameters.
        double evaluatePrior(likely::Parameters const &params);
    protected:
        // The public methods above call these protected methods after making parameter values
        // and changes available via our base class' getParameterValue() and isParameterValueChanged()
        // methods. Any registered changes to parameter values are reset after calling any of these.
        virtual double _evaluate(double r, double mu, double z, bool changed) const = 0;
        virtual double _evaluate(double r, cosmo::Multipole multipole, double z, bool changed) const = 0;
        virtual double _evaluatePrior(bool anyChanged) const;
	}; // AbsCorrelationModel
} // baofit

#endif // BAOFIT_ABS_CORRELATION_MODEL
