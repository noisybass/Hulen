-------
--- Implementacion del cargador de mapas
-------

-- Recibe el nombre del fichero que contiene el 
-- mapa y lo procesa.
-- Asume que el fichero es un fichero Lua que define una 
-- tabla Map global
-- Devuelve un valor booleano indicando si todo fue bien.
function loadMap(mapFile)
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
				else
					AddEntityAttrib(k,v)
				end
			end

			EndMapEntity(key)
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