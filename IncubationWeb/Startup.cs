using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.HttpOverrides;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.OpenApi.Models;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Serialization;
using NLog;
using System;
using System.Globalization;
using System.IO;
using System.Net;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace IncubationWeb
{
    /// <summary>
    /// 
    /// </summary>
    public class Startup
    {
        private readonly Logger logger = LogManager.GetCurrentClassLogger();

        /// <summary>
        /// Initializes a new instance of the <see cref="Startup"/> class.
        /// </summary>
        /// <param name="configuration">The configuration.</param>
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        /// <summary>
        /// Gets the configuration.
        /// </summary>
        /// <value>
        /// The configuration.
        /// </value>
        public IConfiguration Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        /// <summary>
        /// Configures the services.
        /// </summary>
        /// <param name="services">The services.</param>
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddCors();
            services.AddSingleton(logger);
            services.AddControllers().AddNewtonsoftJson(options =>
            {
                options.SerializerSettings.Converters.Add(new StringEnumConverter());
                options.SerializerSettings.NullValueHandling = NullValueHandling.Ignore;
                options.SerializerSettings.ReferenceLoopHandling = ReferenceLoopHandling.Ignore;
                options.SerializerSettings.ContractResolver = new CamelCasePropertyNamesContractResolver();
            });

            services.AddSwaggerGen(c =>
            {
                c.SwaggerDoc("v1", new OpenApiInfo { Title = "GUI API", Version = "v1" });

                string xmlFile = $"{Assembly.GetExecutingAssembly().GetName().Name}.xml";
                string xmlPath = Path.Combine(AppContext.BaseDirectory, xmlFile);
                c.IncludeXmlComments(xmlPath);
                c.EnableAnnotations();

            });

            services.AddSwaggerGenNewtonsoftSupport();
            services.AddRouting(options => options.LowercaseUrls = true);

        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        /// <summary>
        /// Configures the specified application.
        /// </summary>
        /// <param name="app">The application.</param>
        /// <param name="env">The env.</param>
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            app.Use(async (context, next) =>
            {

                logger.Debug(CultureInfo.CurrentCulture, "{@Request}", await formatRequest(context.Request).ConfigureAwait(true));

                Stream originalBodyStream = context.Response.Body;

                using MemoryStream responseBody = new MemoryStream();
                context.Response.Body = responseBody;

                await next.Invoke().ConfigureAwait(true);


                logger.Debug(CultureInfo.CurrentCulture, "{@Response}", await formatResponse(context.Response).ConfigureAwait(true));

                await responseBody.CopyToAsync(originalBodyStream).ConfigureAwait(true);

            });

            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }

            app.UseRouting();
            app.UseAuthentication();
            app.UseAuthorization();

            app.UseStaticFiles();
            app.UseCors(builder => builder.AllowAnyOrigin().AllowAnyHeader().AllowAnyMethod());
            app.UseSwagger();
            app.UseSwaggerUI(c =>
            {
                c.SwaggerEndpoint("/swagger/v1/swagger.json", "My API V1");
                c.DocumentTitle = "Title Documentation";
            });

            app.UseForwardedHeaders(new ForwardedHeadersOptions
            {
                ForwardedHeaders = ForwardedHeaders.XForwardedFor | ForwardedHeaders.XForwardedProto
            });
            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllers();
            });
        }

        private static async Task<object> formatResponse(HttpResponse response)
        {
            response.Body.Seek(0, SeekOrigin.Begin);
            using StreamReader reader = new StreamReader(response.Body, leaveOpen: true);
            string text = await reader.ReadToEndAsync().ConfigureAwait(false);
            response.Body.Seek(0, SeekOrigin.Begin);
            JsonSerializerSettings settings = new JsonSerializerSettings();
            settings.Converters.Add(new StringEnumConverter());
            JToken jo = JToken.FromObject(new { Type = "response", response.StatusCode, StatusCodeValue = (HttpStatusCode)response.StatusCode }, JsonSerializer.Create(settings));
            if (response.ContentType != null)
            {
                if (response.ContentType.Contains("json", StringComparison.OrdinalIgnoreCase))
                {
                    jo["Body"] = JToken.Parse(text);
                }
                else
                {
                    jo["Text"] = text;
                }
            }


            return jo.ToObject<object>();
        }

        private static async Task<object> formatRequest(HttpRequest request)
        {
            request.EnableBuffering();
            Encoding encoder = Encoding.UTF8;

            using StreamReader reader = new StreamReader(request.Body, encoding: encoder, leaveOpen: true);
            string bodyAsText = await reader.ReadToEndAsync().ConfigureAwait(false);
            request.Body.Seek(0, SeekOrigin.Begin);
            JToken jo = JToken.FromObject(new { Type = "request", Request = @$"{request.Scheme}//{request.Host.Host}:{request.Host.Port}/{request.Path.Value}" });
            if (request.QueryString.HasValue)
            {
                jo["QueryString"] = request.QueryString.Value;
            }
            if (request.ContentType != null)
            {
                if (request.ContentType.Contains("json", StringComparison.OrdinalIgnoreCase))
                {
                    jo["Body"] = JToken.Parse(bodyAsText);
                }
                else if (request.ContentType.Contains("xml", StringComparison.OrdinalIgnoreCase))
                {
                    string test = bodyAsText.Remove(46);
                    if (test.Contains("windows-1251", StringComparison.OrdinalIgnoreCase))
                    {
                        encoder = Encoding.GetEncoding("windows-1251");
                        using StreamReader rd = new StreamReader(request.Body, encoding: encoder, leaveOpen: true);
                        jo["Text"] = await rd.ReadToEndAsync().ConfigureAwait(false);
                        request.Body.Seek(0, SeekOrigin.Begin);
                    }
                }
                else
                {
                    jo["Text"] = bodyAsText;
                }
            }

            return jo.ToObject<object>();
        }
    }
}


