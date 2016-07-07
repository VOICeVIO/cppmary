//
// Created by sooda on 16/6/27.
//

#ifndef CPPMARY_LABELGENERATOR_H
#define CPPMARY_LABELGENERATOR_H

#include <features/PhoneTranslator.h>
#include "feature.h"
#include "modules/InterModules.h"
#include <memory>

namespace cppmary {
    class LabelGenerator : public InterModules {
    public:
        LabelGenerator(std::shared_ptr<FeatureProcessorManager> manager, std::shared_ptr<TargetFeatureComputer> featureComputer, std::vector<std::string> featureName, std::vector<std::string> featureAlias, std::shared_ptr<PhoneTranslator> phoneTranslator = nullptr);
        virtual ~LabelGenerator();
        virtual std::string process(std::string input);
        std::vector<Target> createTargetWithPauses(std::vector<pugi::xml_node> segmentsAndPauses,
                                                   std::string pauseSymbol);
    private:
        std::shared_ptr<FeatureProcessorManager> manager_;
        std::shared_ptr<TargetFeatureComputer> featureComputer_;
        std::vector<std::string> featureName_;
        std::vector<std::string> featureAlias_;
        std::shared_ptr<PhoneTranslator> phoneTranslator_;
    };
}

#endif //CPPMARY_LABELGENERATOR_H
