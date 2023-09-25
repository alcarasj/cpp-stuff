from mcr.microsoft.com/cbl-mariner/base/core:2.0
COPY ./bin/server /server
ENTRYPOINT ["/server"]