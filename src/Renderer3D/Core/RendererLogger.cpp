#include <Renderer3D/Core/RendererLogger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Renderer3D{
	std::shared_ptr<spdlog::logger> RendererLogger::coreLogger;
    std::shared_ptr<spdlog::logger> RendererLogger::clientLogger;

	void RendererLogger::Init(){
		spdlog::set_pattern( "%^[%T] %n: %v%$");
		coreLogger = spdlog::stdout_color_mt("GameEngine");
        coreLogger->set_level(spdlog::level::trace);

        // clientLogger = std::make_shared<spdlog::logger>("APP");
        clientLogger = spdlog::stdout_color_mt("APP");
        clientLogger->set_level(spdlog::level::trace);
	}
};
