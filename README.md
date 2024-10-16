# Teste-para-prova
-------------------------------------------
using Lista.Models;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddDbContext<AppDataContext>();
var app = builder.Build();

app.MapGet("/", () => "Hello World!");

app.MapPost("/lista/tarefas/cadastrar", ([FromBody] Tarefa tarefa, [FromServices] AppDataContext ctx) => 
{
    if (string.IsNullOrWhiteSpace(tarefa.Nome))
    {
        return Results.BadRequest("O nome da tarefa é obrigatório.");
    }

    ctx.Tarefas.Add(tarefa);
    ctx.SaveChanges();
    return Results.Created($"/lista/tarefas/buscar/{tarefa.TarefaId}", tarefa);
});

app.MapGet("/lista/tarefas/listar", ([FromServices] AppDataContext ctx) => 
{
    var tarefas = ctx.Tarefas.ToList();
    if (tarefas.Any())
    {
        return Results.Ok(tarefas);
    }
    return Results.NotFound("Nenhuma tarefa encontrada.");
});

app.MapGet("/lista/tarefas/buscar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    var tarefa = ctx.Tarefas.Find(id);
    if (tarefa == null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    return Results.Ok(tarefa);
});

app.MapDelete("/lista/tarefas/deletar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    var tarefa = ctx.Tarefas.Find(id);
    if (tarefa == null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    ctx.Tarefas.Remove(tarefa);
    ctx.SaveChanges();
    return Results.Ok(tarefa);
});

app.Run();

+++++++

using Microsoft.EntityFrameworkCore;

namespace Lista.Models;

public class AppDataContext : DbContext
{
    public DbSet<Tarefa> Tarefas { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseSqlite("Data Source=app.db");
    }
}

++++++++++++++

namespace Lista.Models;

public class Tarefa
{
    public int TarefaId { get; set; }
    public string? Nome { get; set; }
    public DateTime CriadoEm { get; set; } = DateTime.Now;
}


--------------------------------------------------------
###Relacionamento entre tabelas### 

DB -

Um pra um
protected override void OnModelCreating(ModelBuilder modelBuilder)
{
    modelBuilder.Entity<Tabela2>()
        .HasOne(t => t.Tarefa)
        .WithOne()
        .HasForeignKey<Tabela2>(t => t.TarefaId);
}

protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Configuração do relacionamento um-para-muitos
            modelBuilder.Entity<Tabela2>()
                .HasOne(t => t.Tarefa)           // Uma Tabela2 tem uma Tarefa
                .WithMany(t => t.Tabela2s)       // Uma Tarefa tem muitas Tabela2
                .HasForeignKey(t => t.TarefaId); // A Foreign Key é TarefaId
        }

--------------------------------------------------
Criar uma Solution e API

dotnet new sln --output NomeDaSolução ->cd .\NomeSoluçao\

dotnet new web --name NomedaAPI
dentro da solucao
dotnet sln add NomedaAPI

dotnet run --project NomeApi
pegar http://localhost:5258
criar teste.http

criar pasta models
---
namespace Lista.Models;

public class Tarefa
{
    public int TarefaId { get; set; }
    public string? Nome { get; set; }
    public DateTime CriadoEm { get; set; } = DateTime.Now;
}
---
Dentro da API
dotnet add package Microsoft.EntityFrameworkCore.Sqlite
dotnet add package Microsoft.EntityFrameworkCore.Design


dotnet ef migrations add InitialCreate
dotnet ef database update
--------------------

using APITeste.Models;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddDbContext<AppDataContext>();
var app = builder.Build();

app.MapGet("/", () => "Hello World!");

app.MapPost("/apiteste/tarefas/cadastrar", ([FromBody] Tarefa tarefa, [FromServices] AppDataContext ctx) => 
{
    if (string.IsNullOrWhiteSpace(tarefa.Nome))
    {
        return Results.BadRequest("O nome da tarefa é obrigatório.");
    }

    ctx.Tarefas.Add(tarefa);
    ctx.SaveChanges();
    return Results.Created($"/apiteste/tarefas/buscar/{tarefa.TarefaId}", tarefa);
});

app.MapGet("/apiteste/tarefas/listar", ([FromServices] AppDataContext ctx) => 
{
    var tarefas = ctx.Tarefas.ToList();
    if (tarefas.Any())
    {
        return Results.Ok(tarefas);
    }
    return Results.NotFound("Nenhuma tarefa encontrada.");
});

app.MapGet("/apiteste/tarefas/buscar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    var tarefa = ctx.Tarefas.Find(id);
    if (tarefa == null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    return Results.Ok(tarefa);
});

app.MapDelete("/apiteste/tarefas/deletar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    Tarefa? tarefa = ctx.Tarefas.Find(id);
    if (tarefa is null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    ctx.Tarefas.Remove(tarefa);
    ctx.SaveChanges();
    return Results.Ok(tarefa);
});

app.MapPut("/apiteste/tarefas/alterar/{id}", ([FromRoute] int id,
    [FromBody] Tarefa tarefaAlterada, 
    [FromServices] AppDataContext ctx) => 
{
    Tarefa? tarefa = ctx.Tarefas.Find(id);
    if (tarefa is null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    tarefa.Nome = tarefaAlterada.Nome;
    ctx.Tarefas.Update(tarefa);
    ctx.SaveChanges();
    return Results.Ok(tarefa);
});


app.Run();

--------

using Microsoft.EntityFrameworkCore;

namespace APITeste.Models;

public class AppDataContext : DbContext
{
    public DbSet<Tarefa> Tarefas { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseSqlite("Data Source=app.db");
    }
}
-------
namespace APITeste.Models;

public class Tarefa
{
    public int TarefaId { get; set; }
    public string? Nome { get; set; }
    public DateTime CriadoEm { get; set; } = DateTime.Now;
}

--------------------------------------------------------
Relacionamentos
UM pra muitos

namespace APITeste.Models
{
    public class Usuario
    {
        public int UsuarioId { get; set; }
        public string? Nome { get; set; }
        public ICollection<Tarefa> Tarefas { get; set; } = new List<Tarefa>();
    }
}

--

namespace APITeste.Models
{
    public class Tarefa
    {
        public int TarefaId { get; set; }
        public string? Nome { get; set; }
        public DateTime CriadoEm { get; set; } = DateTime.Now;
        
        // Propriedade de chave estrangeira
        public int UsuarioId { get; set; }
        public Usuario Usuario { get; set; }
    }
}

--
namespace APITeste.Models
{
    public class AppDataContext : DbContext
    {
        public DbSet<Tarefa> Tarefas { get; set; }
        public DbSet<Usuario> Usuarios { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("Data Source=app.db");
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Tarefa>()
                .HasOne(t => t.Usuario)
                .WithMany(u => u.Tarefas)
                .HasForeignKey(t => t.UsuarioId);
        }
    }
}

--
app.MapPost("/apiteste/tarefas/cadastrar", ([FromBody] Tarefa tarefa, [FromServices] AppDataContext ctx) => 
{
    var usuario = ctx.Usuarios.Find(tarefa.UsuarioId);
    if (usuario == null)
    {
        return Results.BadRequest("Usuário não encontrado.");
    }

    ctx.Tarefas.Add(tarefa);
    ctx.SaveChanges();
    return Results.Created($"/apiteste/tarefas/buscar/{tarefa.TarefaId}", tarefa);
});

----

####Muitos pra muitos:

namespace APITeste.Models
{
    public class Usuario
    {
        public int UsuarioId { get; set; }
        public string? Nome { get; set; }
        
        // Relacionamento muitos-para-muitos
        public ICollection<Tarefa> Tarefas { get; set; } = new List<Tarefa>();
    }
}

namespace APITeste.Models
{
    public class Tarefa
    {
        public int TarefaId { get; set; }
        public string? Nome { get; set; }
        public DateTime CriadoEm { get; set; } = DateTime.Now;

        // Relacionamento muitos-para-muitos
        public ICollection<Usuario> Usuarios { get; set; } = new List<Usuario>();
    }
}


--
namespace APITeste.Models
{
    public class AppDataContext : DbContext
    {
        public DbSet<Tarefa> Tarefas { get; set; }
        public DbSet<Usuario> Usuarios { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("Data Source=app.db");
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // O EF Core já reconhece automaticamente o relacionamento muitos-para-muitos
            modelBuilder.Entity<Usuario>()
                .HasMany(u => u.Tarefas)
                .WithMany(t => t.Usuarios);
        }
    }
}

Exemplo de API para cadastrar uma tarefa com múltiplos usuários
Aqui está um exemplo de como você poderia cadastrar uma tarefa e associar vários usuários a ela:

csharp
Copiar código
app.MapPost("/apiteste/tarefas/cadastrar", ([FromBody] Tarefa tarefa, [FromServices] AppDataContext ctx) => 
{
    if (tarefa.Usuarios == null || !tarefa.Usuarios.Any())
    {
        return Results.BadRequest("É necessário associar pelo menos um usuário à tarefa.");
    }

    foreach (var usuario in tarefa.Usuarios)
    {
        var usuarioExistente = ctx.Usuarios.Find(usuario.UsuarioId);
        if (usuarioExistente == null)
        {
            return Results.BadRequest($"Usuário com ID {usuario.UsuarioId} não encontrado.");
        }
    }

    ctx.Tarefas.Add(tarefa);
    ctx.SaveChanges();
    return Results.Created($"/apiteste/tarefas/buscar/{tarefa.TarefaId}", tarefa);
});

Exemplo de API para buscar tarefas com seus usuários
csharp
Copiar código
app.MapGet("/apiteste/tarefas/listar", ([FromServices] AppDataContext ctx) => 
{
    var tarefas = ctx.Tarefas.Include(t => t.Usuarios).ToList();
    if (tarefas.Any())
    {
        return Results.Ok(tarefas);
    }
    return Results.NotFound("Nenhuma tarefa encontrada.");
});

Exemplo de API para buscar usuários com suas tarefas
csharp
Copiar código
app.MapGet("/apiteste/usuarios/listar", ([FromServices] AppDataContext ctx) => 
{
    var usuarios = ctx.Usuarios.Include(u => u.Tarefas).ToList();
    if (usuarios.Any())
    {
        return Results.Ok(usuarios);
    }
    return Results.NotFound("Nenhum usuário encontrado.");
});

-------

###Um pra um###

namespace APITeste.Models
{
    public class Usuario
    {
        public int UsuarioId { get; set; }
        public string? Nome { get; set; }
        
        // Relacionamento um-para-um com Tarefa
        public Tarefa? Tarefa { get; set; }
    }
}

namespace APITeste.Models
{
    public class Tarefa
    {
        public int TarefaId { get; set; }
        public string? Nome { get; set; }
        public DateTime CriadoEm { get; set; } = DateTime.Now;

        // Chave estrangeira para garantir relacionamento um-para-um
        public int UsuarioId { get; set; }
        public Usuario Usuario { get; set; }
    }
}

using Microsoft.EntityFrameworkCore;

namespace APITeste.Models
{
    public class AppDataContext : DbContext
    {
        public DbSet<Usuario> Usuarios { get; set; }
        public DbSet<Tarefa> Tarefas { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("Data Source=app.db");
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Configurar relacionamento um-para-um entre Usuario e Tarefa
            modelBuilder.Entity<Usuario>()
                .HasOne(u => u.Tarefa)
                .WithOne(t => t.Usuario)
                .HasForeignKey<Tarefa>(t => t.UsuarioId);  // Tarefa terá a chave estrangeira UsuarioId
        }
    }
}

app.MapPost("/apiteste/usuarios/cadastrar", ([FromBody] Usuario usuario, [FromServices] AppDataContext ctx) => 
{
    if (string.IsNullOrWhiteSpace(usuario.Nome))
    {
        return Results.BadRequest("O nome do usuário é obrigatório.");
    }

    if (usuario.Tarefa == null)
    {
        return Results.BadRequest("É necessário fornecer uma tarefa.");
    }

    ctx.Usuarios.Add(usuario);
    ctx.SaveChanges();
    return Results.Created($"/apiteste/usuarios/buscar/{usuario.UsuarioId}", usuario);
});

app.MapGet("/apiteste/usuarios/buscar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    var usuario = ctx.Usuarios
        .Include(u => u.Tarefa)  // Inclui a tarefa associada ao usuário
        .FirstOrDefault(u => u.UsuarioId == id);

    if (usuario == null)
    {
        return Results.NotFound("Usuário não encontrado.");
    }

    return Results.Ok(usuario);
});







