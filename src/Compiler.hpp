#pragma once

#include <string>

namespace Klang {
    /**
     * @brief Klang compiler.
     *
     */
    class Compiler {
      public:
        /**
         * @brief Construct a new Compiler object.
         *
         * @param source
         */
        Compiler(std::string source);

        /**
         * @brief Generate the target code
         *
         * @return std::string
         */
        std::string generate_target_code();
    };
} // namespace Klang