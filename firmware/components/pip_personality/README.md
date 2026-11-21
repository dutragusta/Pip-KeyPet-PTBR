# Componente de personalidade do Pip

Este componente reutiliza diretamente `pet.c`, `pet.h` e `moods.h` do submódulo upstream `vendor/pip-keypet`. Não inclui o entry point do firmware original nem inicializa periféricos.

## Responsabilidades

- Simular fome, energia, diversão, carinho, caminhada, sono e humor.
- Processar eventos de interação e devolver uma reação `PIP_*`.
- Expor os indicadores para a interface.
- Exportar e restaurar o estado `pet_t` com validação de versão.

## Exemplo de uso

```c
#include "pip_personality.h"

static pip_personality_t pip;

void character_init(int64_t now)
{
    pip_personality_init(&pip, now, -180, 0x504950u);
}

int character_feed(int64_t now)
{
    return pip_personality_event(&pip, PIP_PERSONALITY_FEED, now);
}

void character_tick(int64_t now)
{
    pip_personality_status_t status;
    pip_personality_update(&pip, now);
    if (pip_personality_get_status(&pip, &status)) {
        /* Enviar status.mood e status.* para a camada visual. */
    }
}
```

O fuso horário é informado em minutos em relação ao UTC. Para São Paulo, use `-180` enquanto o horário local for UTC-3.

## Persistência

O componente não escolhe NVS, arquivo ou outro backend. O firmware Muse deve armazenar os bytes retornados por `pip_personality_export` e recuperá-los com `pip_personality_restore`. O snapshot contém a estrutura versionada original `pet_t`; se a versão mudar, a restauração é rejeitada em vez de interpretar dados antigos incorretamente.

## Testes

Com os submódulos inicializados, execute:

```sh
sh tests/personality/run.sh
```

O teste compila o motor original e a camada adaptadora com o compilador C do host. Isso valida a lógica portátil, não o firmware ESP-IDF completo.
