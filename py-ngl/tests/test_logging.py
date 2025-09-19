import ngl

# This should trigger the logging configuration in ngl/__init__.py

# Now, let's use a class that has logging
# This should print a debug message to the console and NGLDebug.log
img = ngl.Image(width=100, height=100, mode=ngl.ImageModes.RGB)

# You can also log directly from your application code
# note we can get the logger from the ngl module as we created it there
logger = ngl.logger
logger.info("This is an info message from the application")
logger.warning("This is a warning message")
logger.error("This is an error message")

print("Logging test finished. Check the console and NGLDebug.log for output.")
