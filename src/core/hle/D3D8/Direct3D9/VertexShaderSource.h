
#ifndef DIRECT3D9SHADERCACHE_H
#define DIRECT3D9SHADERCACHE_H

#include "VertexShader.h"
#include <map>

typedef uint64_t ShaderKey;

// Manages creation and caching of vertex shaders
class VertexShaderSource {

public:
	ShaderKey CreateShader(const DWORD* pXboxFunction, DWORD* pXboxFunctionSize);
	IDirect3DVertexShader *GetShader(ShaderKey key);
	void ReleaseShader(ShaderKey key);

	void ResetD3DDevice(IDirect3DDevice* pD3DDevice);

	// TODO
	// WriteCacheToDisk
	// LoadCacheFromDisk

private:
	struct LazyVertexShader {
		bool isReady = false;
		std::future<ID3DBlob*> compileResult;
		IDirect3DVertexShader* pHostVertexShader = nullptr;

		// TODO when is it a good idea to releas eshaders?
		int referenceCount = 0;

		// TODO persist shaders to disk
		// ShaderVersion?
		// OptimizationLevel?
	};

	IDirect3DDevice* pD3DDevice;
	std::mutex cacheMutex;
	std::map<ShaderKey, LazyVertexShader> cache;

	bool VertexShaderSource::_FindShader(ShaderKey key, LazyVertexShader** ppLazyShader);
};

#endif
