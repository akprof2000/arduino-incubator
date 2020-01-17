using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.EventLog;
using NLog;
using NLog.Web;
using System;
using System.Globalization;
using System.IO;
using WebService;

namespace IncubationWeb
{
    /// <summary>
    /// 
    /// </summary>
    public static class Program
    {

        /// <summary>
        /// Defines the entry point of the application.
        /// </summary>
        /// <param name="args">The arguments.</param>
        public static void Main(string[] args)
        {

            Logger logger = NLogBuilder.ConfigureNLog("nlog.config").GetCurrentClassLogger();

            logger.Info(" ");
            logger.Info($"***********************************************************************");
            logger.Info($"*                 Program start at {DateTime.Now.ToString("dd.MM.yyyy HH:mm:ss", CultureInfo.CurrentCulture)}                *");
            logger.Info($"*                            Version {System.Reflection.Assembly.GetEntryAssembly().GetName().Version}                          *");
            logger.Info($"***********************************************************************");
            logger.Info(" ");
            try
            {
                IConfigurationBuilder builder = new ConfigurationBuilder()
                .SetBasePath(Directory.GetCurrentDirectory())
                .AddJsonFile("appsettings.json", optional: true, reloadOnChange: true);
                IConfigurationRoot configuration = builder.Build();

                CreateHostBuilder(args, configuration["StartingPort"].ConvertTo<int>()).Build().Run();
            }
            catch (Exception ex)
            {
                logger.Fatal(ex, "Stopped program because of exception");
                throw;
            }
            finally
            {
                logger.Info(" ");
                logger.Info($"***********************************************************************");
                logger.Info($"*                  Program end at {DateTime.Now.ToString("dd.MM.yyyy HH:mm:ss", CultureInfo.CurrentCulture)}                 *");
                logger.Info($"*                            Version {System.Reflection.Assembly.GetEntryAssembly().GetName().Version}                          *");
                logger.Info($"***********************************************************************");
                logger.Info(" ");

                LogManager.Shutdown();
            }

        }

        /// <summary>
        /// Creates the host builder.
        /// </summary>
        /// <param name="args">The arguments.</param>
        /// <param name="port">The port.</param>
        /// <returns></returns>
        public static IHostBuilder CreateHostBuilder(string[] args, int port)
        {
            return Host.CreateDefaultBuilder(args)
                .UseWindowsService()
                .ConfigureServices(services =>
                {
                    services.Configure<EventLogSettings>(config =>
                    {
                        config.LogName = "Incubation API Service";
                        config.SourceName = "Incubation API Service Source";
                    });
                })
                .ConfigureWebHostDefaults(webBuilder =>
                {
                    webBuilder.UseStartup<Startup>().UseKestrel(opt => { opt.ListenAnyIP(port); });
                }).ConfigureLogging(logging =>
                {
                    logging.ClearProviders();
                    logging.SetMinimumLevel(Microsoft.Extensions.Logging.LogLevel.Trace);
                })
                .UseNLog();
        }

    }
}
