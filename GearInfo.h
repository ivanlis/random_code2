#ifndef GEAR_INFO_H_
#define GEAR_INFO_H_

#include <string>
#include <vector>

namespace gearplot
{
    struct SearchInputParameters
    {
        SearchInputParameters(): partId(-1), geometryId(-1), numTeeth(-1) { }
        int partId;
        int geometryId;
        int numTeeth;
        std::string directory;
    };

    struct ProfileInfo
    {
        ProfileInfo(): rootDiameter(0.0), tipDiameter(0.0), lineAX(0.0), lineAY(0.0), lineBX(0.0), lineBY(0.0),
            totalProfileError(0.0), totalProfileNegTol(0.0), totalProfilePosTol(0.0),
            formError(0.0), formErrorNegTol(0.0), formErrorPosTol(0.0), 
            slopeError(0.0), slopeErrorNegTol(0.0), slopeErrorPosTol(0.0), 
            pitchDev(0.0), cumulativePitchError(0.0), runoutComponent(0.0) { }

        double rootDiameter;
        double tipDiameter;
        double lineAX;
        double lineAY;
        double lineBX;
        double lineBY;
        double totalProfileError;
        double totalProfileNegTol;
        double totalProfilePosTol;
        double formError;
        double formErrorNegTol;
        double formErrorPosTol;
        double slopeError;
        double slopeErrorNegTol;
        double slopeErrorPosTol;
        double pitchDev;
        double cumulativePitchError;
        double runoutComponent;
    };

    struct LeadInfo
    {
        LeadInfo(): minHeight(0.0), maxHeight(0.0), lineAX(0.0), lineAY(0.0), lineBX(0.0), lineBY(0.0),
            totalLeadError(0.0), totalLeadNegTol(0.0), totalLeadPosTol(0.0), 
            formError(0.0), formErrorNegTol(0.0), formErrorPosTol(0.0),
            helixSlopeError(0.0), helixSlopeNegTol(0.0), helixSlopePosTol(0.0),
            pitchDev(0.0), cumulativePitchError(0.0), runoutComponent(0.0) { }
        double minHeight;
        double maxHeight;
        double lineAX;
        double lineAY;
        double lineBX;
        double lineBY;
        double totalLeadError;
        double totalLeadNegTol;
        double totalLeadPosTol;
        double formError;
        double formErrorNegTol;
        double formErrorPosTol;
        double helixSlopeError;
        double helixSlopeNegTol;
        double helixSlopePosTol;
        double pitchDev;
        double cumulativePitchError;
        double runoutComponent;       
    };

    struct ToothInfo
    {
        ProfileInfo leftProfile;
        ProfileInfo rightProfile;
        LeadInfo leftLead;
        LeadInfo rightLead;

        double totalProfileError;
        double totalLeadError;
    };

    struct GearInfo
    {
        //typedef std::vector<ProfileInfo> Profiles;
        //typedef std::vector<LeadInfo> Leads;
        typedef std::vector<ToothInfo> Teeth;

        GearInfo(): partId(-1), geometryId(-1) { }

        void resize(int numTeeth);

        int partId;
        int geometryId;

        //Profiles profiles;
        //Leads leads;
        Teeth teeth;
    };

    class GearInfoImporter
    {
        public:
        static void import(const std::string& filename, GearInfo& gear, int toothId, char zone, char side);
    };
}

#endif //GEAR_INFO_H_