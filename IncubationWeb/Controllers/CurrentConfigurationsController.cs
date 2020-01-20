using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace IncubationWeb.Controllers
{
    /// <summary>
    /// 
    /// </summary>
    /// <seealso cref="Microsoft.AspNetCore.Mvc.ControllerBase" />
    [Route("api/[controller]")]
    [ApiController]
    public class CurrentConfigurationsController : ControllerBase
    {
        private readonly IncubDbContext _context;

        /// <summary>
        /// Initializes a new instance of the <see cref="CurrentConfigurationsController"/> class.
        /// </summary>
        /// <param name="context">The context.</param>
        public CurrentConfigurationsController(IncubDbContext context)
        {
            _context = context;
        }

        // GET: api/CurrentConfigurations
        /// <summary>
        /// Gets the configuration.
        /// </summary>
        /// <returns></returns>
        [HttpGet]
        public async Task<ActionResult<IEnumerable<CurrentConfiguration>>> GetConfig()
        {
            return await _context.Config.ToListAsync().ConfigureAwait(true);
        }

        // GET: api/CurrentConfigurations/5
        /// <summary>
        /// Gets the current configuration.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns></returns>
        [HttpGet("{id}")]
        public async Task<ActionResult<CurrentConfiguration>> GetCurrentConfiguration(int id)
        {
            CurrentConfiguration currentConfiguration = await _context.Config.FindAsync(id);

            if (currentConfiguration == null)
            {
                return NotFound();
            }

            return currentConfiguration;
        }

        // PUT: api/CurrentConfigurations/5
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for
        // more details see https://aka.ms/RazorPagesCRUD.
        /// <summary>
        /// Puts the current configuration.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="currentConfiguration">The current configuration.</param>
        /// <returns></returns>
        [HttpPut("{id}")]
        public async Task<IActionResult> PutCurrentConfiguration(int id, CurrentConfiguration currentConfiguration)
        {
            if (id != currentConfiguration?.Id)
            {
                return BadRequest();
            }

            _context.Entry(currentConfiguration).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync().ConfigureAwait(true);
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!currentConfigurationExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        // POST: api/CurrentConfigurations
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for
        // more details see https://aka.ms/RazorPagesCRUD.
        /// <summary>
        /// Posts the current configuration.
        /// </summary>
        /// <param name="currentConfiguration">The current configuration.</param>
        /// <returns></returns>
        [HttpPost]
        public async Task<ActionResult<CurrentConfiguration>> PostCurrentConfiguration(CurrentConfiguration currentConfiguration)
        {
            _context.Config.Add(currentConfiguration);
            await _context.SaveChangesAsync().ConfigureAwait(true);

            return CreatedAtAction("GetCurrentConfiguration", new { id = currentConfiguration?.Id }, currentConfiguration);
        }

        // DELETE: api/CurrentConfigurations/5
        /// <summary>
        /// Deletes the current configuration.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns></returns>
        [HttpDelete("{id}")]
        public async Task<ActionResult<CurrentConfiguration>> DeleteCurrentConfiguration(int id)
        {
            CurrentConfiguration currentConfiguration = await _context.Config.FindAsync(id);
            if (currentConfiguration == null)
            {
                return NotFound();
            }

            _context.Config.Remove(currentConfiguration);
            await _context.SaveChangesAsync().ConfigureAwait(true);

            return currentConfiguration;
        }

        /// <summary>
        /// Currents the configuration exists.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns></returns>
        private bool currentConfigurationExists(int id)
        {
            return _context.Config.Any(e => e.Id == id);
        }
    }
}
