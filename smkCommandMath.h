#pragma once

#include "smkCommandBase.h"

namespace smk {
namespace Command {
class Math : public Base
{
    itk::ImageIOBase::Pointer m_IO;

    std::string m_out;
    std::string m_input1;
    std::string m_operator;
    std::string m_component;
    std::string m_input2;
    double m_constant;

    virtual std::string _doc();
    virtual int _execute(std::map<std::string, docopt::value> args);

    std::string evaluate_par(std::string & s);

    template <typename ComponentType, int Dimension>
    void _check_if_components_are_vectors();

    template <typename IputType, typename OutputType>
    void _create_filter();

    template <typename FilterType>
    void _compute_output(FilterType* filter);
};

} // EON Command
} // EON Math

#include "smkCommandMath.hpp"
