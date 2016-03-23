State_Prueba = {}

State_Prueba["Enter"] = function(CFSMEntity)

	print ("[Lua]: Enter")

end

State_Prueba["Execute"] = function(CFSEntity)

	CFSMEntity: SayHello()

end

State_Prueba["Exit"] = function(CFSMEntity)

	print ("[Lua]: Exit")

end