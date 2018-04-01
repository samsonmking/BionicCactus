#include <web/index_connected/IndexConnectedGetRequestHandler.hpp>

IndexConnectedGetRequestHandler::IndexConnectedGetRequestHandler(Header &header, const char *lightUri) : 
_header(header),
_lightUri(lightUri) {

}

const char *getURI() {
    return "/";
}

void IndexConnectedGetRequestHandler::getHTML(char *out, size_t len) {
    char *pos = out;
    char *end = out + len;
    pos += _header.getHeader(pos, end - pos);
    const char *body = R"(<h2>Settings</h2>
	    <ul>
	    	<li><a href="/config/light">Light</a></li>
	    </ul>
	</body>
</html>)";
    pos += snprintf(pos, end - pos, body);
}
