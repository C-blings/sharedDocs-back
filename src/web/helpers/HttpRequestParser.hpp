#pragma once

#include <boost/algorithm/string/trim.hpp>
#include <cmath>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

#include <web/models/HttpRequest.hpp>

namespace web_layout{

    class HttpRequestParser{
        private:
            static inline std::unordered_map<std::string, Method> string_to_method = {
                {"GET", Method::GET},
                {"POST", Method::POST},
                {"PUT", Method::PUT},
                {"DELETE", Method::DELETE},
                {"OPTIONS", Method::OPTIONS},
            };
        public:

            // cast string request to data structure
            static HttpRequest GetHttpRequest(const std::string& request) {
                std::vector<std::string> request_lines;
                boost::split(request_lines, request, boost::is_any_of("\n\r"), boost::token_compress_off);

				std::vector<std::string> method_and_path;
				boost::split(method_and_path, request_lines[0], boost::is_any_of(" "), boost::token_compress_on);

				Method method = string_to_method[method_and_path[0]];
				std::string path = method_and_path[1];
				std::unordered_map<std::string, std::string> headers, parameters;

                auto parameters_separator = path.find('?');
                if (parameters_separator != std::string::npos){
                    std::cout << "looking for params\n";
                    std::string parameters_string = path.substr(parameters_separator + 1);
                    path = path.substr(0, parameters_separator);
                    std::vector<std::string> parameters_part;
                    boost::split(parameters_part,  parameters_string, boost::is_any_of(";"), boost::token_compress_on);
                    for (std::string& parameter : parameters_part){
                        auto separator = parameter.find('=');
                        std::string key = parameter.substr(0, separator),
                                    value = parameter.substr(separator + 1);
                        std::cout << key << ' ' << value << '\n';
                        parameters[key] = value;
                    }
                }

				std::string body;

				int i;
				for(i = 2; i < request_lines.size(); i += 2) {
                    boost::trim(request_lines[i]);

					if(request_lines[i].empty()) {
                        i += 2;
                        break;
					}

					std::vector<std::string> header;

					boost::split(header,  request_lines[i], boost::is_any_of(": "), boost::token_compress_on);
                    
                    headers.emplace(header[0], header[1]);
				}

				for(; i < request_lines.size(); ++i) {
                        boost::trim(request_lines[i]);
						body += request_lines[i];
                        if(i != request_lines.size() - 1) {
                            body += "\n";
                        }
				}

                return HttpRequest(method, path, headers, body, parameters);
            }
    };

}
