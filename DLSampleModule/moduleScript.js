function init() {
	script.log("Initialize custom module using dynamic library");
	reload();
}

var dynamicLibrary = undefined;
var hello = undefined;
var math = undefined;
function reload() {
	if (dynamicLibrary) {
		util.unloadDynamicLibrary(dynamicLibrary);
		dynamicLibrary = undefined;
		hello = undefined;
		math = undefined;
	}
	var dynamicLibraryPath = local.parameters.dynamicLibraryPath.getAbsolutePath();
	if (dynamicLibraryPath === '') {
		script.logWarning('dynamic library path is empty');
		return;
	}
	script.log('reload dynamic library', dynamicLibraryPath);
	dynamicLibrary = util.loadDynamicLibrary(dynamicLibraryPath);
	if (!dynamicLibrary) {
		script.logError('dynamic library loading failed');
		return;
	}
	hello = util.findFunctionInDynamicLibrary(dynamicLibrary, "hello");
	if (!hello) {
		script.logError('hello function not found in dynamic library');
	}
	math = util.findFunctionInDynamicLibrary(dynamicLibrary, "math");
	if (!math) {
		script.logError('math function not found in dynamic library');
	}
}

function moduleParameterChanged(param) {
	if (param.name === "dynamicLibraryPath") {
		reload();
	}
}

function helloCmd(val) {
	if (hello) {
		hello(val);
	}
	else {
		script.logError('dynamic library is not loaded');
	}
}

function mathCmd(left, right) {
	if (math) {
		script.log(JSON.stringify(math({ left: left, right: right })));
	}
	else {
		script.logError('dynamic library is not loaded');
	}
}
