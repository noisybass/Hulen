-------
--- Implementacion del cargador de mapas
-------

-- Recibe el nombre del fichero que contiene el 
-- mapa y lo procesa.
-- Asume que el fichero es un fichero Lua que define una 
-- tabla Map global
-- Devuelve un valor booleano indicando si todo fue bien.
function loadMap(mapFile)
	SayHello("Vamos a empezar con las entidades")
	print("Loading map...")
	Map_GO = {};
	Map = {};
	-- Una manera mejor de hacerlo
	-- local file = loadFile(...)
	-- file()

	dofile (mapFile);

	if Map == nil or Map_GO == nil then
		return 0
	else
		--printByConsole (Map_GO)
		parseMap(Map_GO)
		--printByConsole (Map)
		parseMap(Map)
	end

end

function parseMap(map)
	for key, value in pairs(map) do
			BeginMapEntity(key)

			for k,v in pairs(value) do
				if type(v) == "table" then
					AddEntityAttrib(k, v[1].." "..v[2].." "..v[3])
				elseif type(v) == "string" then
					AddEntityAttrib(k,v)
				else
					AddEntityAttrib(k, tostring(v))
				end
			end

			EndMapEntity(key)
		end
end

--[[
	Parsing Prefab
]]--

function loadPrefab(prefabFile)
	SayHello("Vamos a empezar con los prefabs")
	print ("Loading prefab map...")
	Prefab_GO = {};
	Prefab = {};

	dofile(prefabFile);

	if Prefab == nil or Prefab_GO == nil then
		return 0
	else
		--printByConsole (Map_GO)
		parsePrefab(Prefab_GO)
		--printByConsole (Map)
		parsePrefab(Prefab)
	end

end

function parsePrefab(map)
	for key, value in pairs(map) do
			BeginPrefabEntity(key)

			for k,v in pairs(value) do
				if type(v) == "table" then
					AddPrefabAttrib(k, v[1].." "..v[2].." "..v[3])
				elseif type(v) == "string" then
					AddPrefabAttrib(k,v)
				else
					AddPrefabAttrib(k, tostring(v))
				end
			end

			EndPrefabEntity(key)
		end
end

function printByConsole(map)
	for key, value in pairs(map) do
			print (key)
			for k,v in pairs(value) do
				if type(v) == "table" then
					print("   " ..k.." = ("..v[1]..", "..v[2]..", "..v[3]..")")
				else
					print("   "..k.." = "..tostring(v))
				end
			end
		end
end