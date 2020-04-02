#ifndef GEOMETRY_PLOT_DATA_EXPORTER_H_
#define GEOMETRY_PLOT_DATA_EXPORTER_H_

#include <string>
#include <boost/property_tree/ptree.hpp>
#include "GearInfo.h"

namespace pt = boost::property_tree;

namespace gearplot
{
    class GeometryPlotDataExporter
    {
        public:
        static void exportToJson(const std::string& pathname, const GearInfo& geometry);

        static void buildPropertyTree(pt::ptree& tree, const GearInfo& geometry);
        static void buildProfileNode(pt::ptree& node, const ProfileInfo& profile);
        static void buildLeadNode(pt::ptree& node, const LeadInfo& lead);
    };
}

#endif //GEOMETRY_PLOT_DATA_EXPORTER_H_
