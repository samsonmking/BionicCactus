#ifndef INDEX_CONNECTED_H
#define INDEX_CONNECTED_H

#include <Arduino.h>
#include "web/GetRequestHandler.hpp"
#include "web/Header.hpp"
#include "IndexDashboard.hpp"

namespace Web {

    class IndexConnectedGetRequestHandler : public GetRequestHandler {
    public:
        IndexConnectedGetRequestHandler(Header &header, 
        const char *lightUri, 
        const char *pumpUri, 
        const char *soilUri, 
        const char *runLoopUri, 
        const char *emailUri,
        const char *bottleUri,
        IndexDashboard& dashboard);
        inline virtual const char *getURI() override {
                return "/";
        };
        virtual void getHTML(char *out, size_t len) override;
    private:
        Header _header;
        const char *_lightUri;
        const char *_pumpUri;
        const char *_soilUri;
        const char *_runLoopUri;
        const char *_emailUri;
        const char *_bottleUri;
        IndexDashboard& _dashboard;
    };

}


#endif
