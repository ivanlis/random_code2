#include "GeometryPlotDataExporter.h"
#include <iostream>
#include <boost/property_tree/json_parser.hpp>

using namespace gearplot;

void GeometryPlotDataExporter::exportToJson(const std::string& pathname, const GearInfo& geometry)
{
    pt::ptree tree;
    buildPropertyTree(tree, geometry);
    pt::write_json(pathname, tree);
}

void GeometryPlotDataExporter::buildPropertyTree(pt::ptree& tree, const GearInfo& geometry)
{
    // gear attributes
    tree.put("gearAttr.partId", geometry.partId);
    tree.put("gearAttr.geomId", geometry.geometryId);
    tree.put("gearAttr.totalProfileError", geometry.totalProfileError);
    tree.put("gearAttr.totalLeadError", geometry.totalLeadError);
    tree.put("gearAttr.rootDiameter", geometry.rootDiameter);
    tree.put("gearAttr.tipDiameter", geometry.tipDiameter);
    tree.put("gearAttr.minHeight", geometry.minHeight);
    tree.put("gearAttr.maxHeight", geometry.maxHeight);
    tree.put("gearAttr.totalProfileNegTol", geometry.totalProfileNegTol);
    tree.put("gearAttr.totalProfilePosTol", geometry.totalProfilePosTol);
    tree.put("gearAttr.totalLeadNegTol", geometry.totalLeadNegTol);
    tree.put("gearAttr.totalLeadPosTol", geometry.totalLeadPosTol);
    tree.put("gearAttr.profileFormNegTol", geometry.profileFormNegTol);
    tree.put("gearAttr.profileFormPosTol", geometry.profileFormPosTol);
    tree.put("gearAttr.leadFormNegTol", geometry.leadFormNegTol);
    tree.put("gearAttr.leadFormPosTol", geometry.leadFormPosTol);
    tree.put("gearAttr.profileSlopeNegTol", geometry.profileSlopeNegTol);
    tree.put("gearAttr.profileSlopePosTol", geometry.profileSlopePosTol);
    tree.put("gearAttr.helixSlopeNegTol", geometry.helixSlopeNegTol);
    tree.put("gearAttr.helixSlopePosTol", geometry.helixSlopePosTol);

    // teeth
    for (size_t i = 0; i != geometry.teeth.size(); ++i)
    {
        pt::ptree node;
        
        // node.put("gearToothAttr.totalProfileError", geometry.teeth[i].totalProfileError);
        // node.put("gearToothAttr.totalLeadError", geometry.teeth[i].totalLeadError);
        // node.put("gearToothAttr.rootDiameter", geometry.teeth[i].rootDiameter);
        // node.put("gearToothAttr.tipDiameter", geometry.teeth[i].tipDiameter);
        // node.put("gearToothAttr.minHeight", geometry.teeth[i].minHeight);
        // node.put("gearToothAttr.maxHeight", geometry.teeth[i].maxHeight);


        node.put("toothAttr.runoutComponent", geometry.teeth[i].runoutComponent);

        pt::ptree child;
        buildProfileNode(child, geometry.teeth[i].rightProfile);
        node.add_child("rightProfile", child);
        child.clear();
        buildProfileNode(child, geometry.teeth[i].leftProfile);
        node.add_child("leftProfile", child);
        child.clear();
        buildLeadNode(child, geometry.teeth[i].rightLead);
        node.add_child("rightLead", child);
        child.clear();
        buildLeadNode(child, geometry.teeth[i].leftLead);
        node.add_child("leftLead", child);

        tree.add_child("teeth." + std::to_string(i), node);
    }
}

void GeometryPlotDataExporter::buildProfileNode(pt::ptree& node, const ProfileInfo& profile)
{
    node.put("gearProfileAttr.lineAX", profile.lineAX);
    node.put("gearProfileAttr.lineAY", profile.lineAY);
    node.put("gearProfileAttr.lineBX", profile.lineBX);
    node.put("gearProfileAttr.lineBY", profile.lineBY);
    node.put("gearProfileAttr.totalProfileError", profile.totalProfileError);
    //node.put("gearProfileAttr.totalProfileNegTol", profile.totalProfileNegTol);
    //node.put("gearProfileAttr.totalProfilePosTol", profile.totalProfilePosTol);
    node.put("gearProfileAttr.formError", profile.formError);
    //node.put("gearProfileAttr.formErrorNegTol", profile.formErrorNegTol);
    //node.put("gearProfileAttr.formErrorPosTol", profile.formErrorPosTol);
    node.put("gearProfileAttr.slopeError", profile.slopeError);
    node.put("gearProfileAttr.slopeErrorNegTol", profile.slopeErrorNegTol);
    node.put("gearProfileAttr.slopeErrorPosTol", profile.slopeErrorPosTol);
    node.put("gearProfileAttr.pitchDev", profile.pitchDev);
    node.put("gearProfileAttr.pitchError", profile.pitchError);
    node.put("gearProfileAttr.cumulativePitchError", profile.cumulativePitchError);
    //node.put("gearProfileAttr.runoutComponent", profile.runoutComponent);

    pt::ptree deviationNode;
    buildDeviationNode(deviationNode, profile.deviationX, profile.deviationY);
    node.add_child("gearProfileDeviations", deviationNode);
}

void GeometryPlotDataExporter::buildLeadNode(pt::ptree& node, const LeadInfo& lead)
{
    node.put("gearLeadAttr.lineAX", lead.lineAX);
    node.put("gearLeadAttr.lineAY", lead.lineAY);
    node.put("gearLeadAttr.lineBX", lead.lineBX);
    node.put("gearLeadAttr.lineBY", lead.lineBY);
    node.put("gearLeadAttr.totalLeadError", lead.totalLeadError);
    //node.put("gearLeadAttr.totalLeadNegTol", lead.totalLeadNegTol);
    //node.put("gearLeadAttr.totalLeadPosTol", lead.totalLeadPosTol);
    node.put("gearLeadAttr.formError", lead.formError);
    //node.put("gearLeadAttr.formErrorNegTol", lead.formErrorNegTol);
    //node.put("gearLeadAttr.formErrorPosTol", lead.formErrorPosTol);
    node.put("gearLeadAttr.helixSlopeError", lead.helixSlopeError);
    //node.put("gearLeadAttr.helixSlopeNegTol", lead.helixSlopeNegTol);
    //node.put("gearLeadAttr.helixSlopePosTol", lead.helixSlopePosTol);
    node.put("gearLeadAttr.pitchDev", lead.pitchDev);

    pt::ptree deviationNode;
    buildDeviationNode(deviationNode, lead.deviationX, lead.deviationY);
    node.add_child("gearLeadDeviations", deviationNode);
}

void GeometryPlotDataExporter::buildDeviationNode(pt::ptree& node, const std::vector<double>& x, const std::vector<double>& y)
{
    if (x.empty() || y.empty())
        return;

    pt::ptree devArrayNode;
    for (auto cit = x.begin(); cit != x.end(); ++cit)
    {
        pt::ptree child;
        //std::cout << "Putting x child with value: " << *cit << std::endl;
        //child.put(std::to_string(*cit), "");
        child.put("", *cit);
        devArrayNode.push_back(std::make_pair("", child));
    }
    node.add_child("x", devArrayNode);
    devArrayNode.clear();
    for (auto cit = y.begin(); cit != y.end(); ++cit)
    {
        pt::ptree child;
        //std::cout << "Putting y child with value: " << *cit << std::endl;
        //child.put(std::to_string(*cit), "");
        child.put("", *cit);
        devArrayNode.push_back(std::make_pair("", child));
    }
    node.add_child("y", devArrayNode);
}
